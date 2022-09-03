#include "charclass.hpp"

#include <string>
#include <set>
#include <ostream>
#include <algorithm>
#include <vector>

namespace rematch {

CharClassBuilder::CharClassBuilder():	nchars_(0) {}

CharClassBuilder::CharClassBuilder(char c): nchars_(0) { add_single(c); }

CharClassBuilder::CharClassBuilder(char l, char h): nchars_(0) { add_range(l,h); }

CharClassBuilder::CharClassBuilder(REmatchParser::LiteralContext *ctx): nchars_(0) {
    if (ctx->escapes()) {
        add_single(ctx->getText()[1]);
    } else if (ctx->special()) {
        auto s = ctx->special();
        if (s->TAB()) {
            add_single('\t');
        } else if (s->CARRIAGE_RETURN()) {
            add_single('\r');
        } else if (s->NEWLINE()) {
            add_single('\n');
        } else if (s->VERTICAL_WHITESPACE()) {
            add_single('\v');
        } else if (s->FORM_FEED()) {
            add_single('\f');
        }
    } else {
        add_single(ctx->getText()[0]);
    }
}

CharClassBuilder::CharClassBuilder(REmatchParser::SharedAtomContext *ctx): nchars_(0) {
    if (ctx->DECIMAL_DIGIT()) {
        add_range(0, 9);
    } else if (ctx->NOT_DECIMAL_DIGIT()) {
        add_range(0, 9);
        negate();
    } else if (ctx->WHITESPACE()) {
        add_single(' ');
        add_single('\t');
        add_single('\r');
        add_single('\n');
        add_single('\v');
        add_single('\f');
    } else if (ctx->NOT_WHITESPACE()) {
        add_single(' ');
        add_single('\t');
        add_single('\r');
        add_single('\n');
        add_single('\v');
        add_single('\f');
        negate();
    } else if (ctx->ALPHANUMERIC()) {
        add_range('A', 'Z');
        add_range('a', 'z');
        add_range('0', '9');
        add_single('_');
    } else if (ctx->NOT_ALPHANUMERIC()) {
        add_range('A', 'Z');
        add_range('a', 'z');
        add_range('0', '9');
        add_single('_');
        negate();
    } else {
        // TODO: Change this error message
        throw std::runtime_error("Unknown shared atom: '" + ctx->getText() + "'");
    }
}

CharClassBuilder::CharClassBuilder(REmatchParser::CharacterClassContext *ctx): nchars_(0) {
    for (auto &ccAtom : ctx->ccAtom()) {
        if (ccAtom->ccRange()) {
            auto cr = ccAtom->ccRange();
            auto l_lo = cr->ccLiteral(0);
            auto l_hi = cr->ccLiteral(1);

            char lo;
            if (l_lo->ccEscapes()) {
                lo = l_lo->getText()[1];
            } else {
                lo = l_lo->getText()[0];
            }
            char hi;
            if (l_hi->ccEscapes()) {
                hi = l_hi->getText()[1];
            } else {
                hi = l_hi->getText()[0];
            }
            add_range(lo, hi);
        } else if (ccAtom->sharedAtom()) {
            REmatchParser::SharedAtomContext* sa(ccAtom->sharedAtom());
            CharClassBuilder cb_sharedAtom(sa);
            add_charclass(&cb_sharedAtom);
        } else if (ccAtom->literal()) {
            REmatchParser::LiteralContext* lc(ccAtom->literal());
            CharClassBuilder cb_literal(lc);
            add_charclass(&cb_literal);
        } else {
            // TODO: Change this error message
            throw std::runtime_error("Unknown Character Class Atom: '" + ccAtom->getText() + "'");
        }
    }
    if (ctx->HAT()) {
        negate();
    }
}

bool CharClassBuilder::add_range(char lo, char hi) {
	if (hi < lo)
		return false;

	{
		auto it = ranges_.find(CharRange(lo, hi));
		if (it != end() && it->lo <= lo && hi <= it->hi)
			return false;
	}

	// Look for an inmediate range to the left of [lo, hi]. If exists
	// then erase and extend [lo, hi] accordingly
	if(lo > 0) {
		auto it = ranges_.find(CharRange(lo-1, lo-1));
		if(it != end()) {
			lo = it->lo;
			if(it->hi > hi)
				hi = it->hi;
			nchars_ -= it->hi - it->lo + 1;
			ranges_.erase(it);
		}
	}
	// Look for an inmediate range to the right of [lo, hi]. If exists
	// then erase and extend [lo, hi] accordingly
	if(hi < CHAR_MAX) {
		auto it = ranges_.find(CharRange(hi+1, hi+1));
		if(it != end()) {
			hi = it->hi;
			// Not necesary to check for lo. Did it in previous step.
			nchars_ -= it->hi - it->lo + 1;
			ranges_.erase(it);
		}
	}

	// Search for ranges inside [lo, hi]. Erase them.
	// The remaining ranges that overlap with [lo, hi] must be inside
	// it.
	for(;;) {
		auto it = ranges_.find(CharRange(lo, hi));
		if(it == end())
			break;
		nchars_ -= it->hi - it->lo + 1;
		ranges_.erase(it);
	}

	// Add [lo, hi]
	nchars_ += hi - lo + 1;
	ranges_.insert(CharRange(lo, hi));
	return true;
}

bool CharClassBuilder::add_single(char c) {
	return add_range(c, c);
}

void CharClassBuilder::add_charclass(CharClassBuilder *cc) {
	for(iterator it = cc->begin(); it != cc->end(); it++) {
		add_range(it->lo, it->hi);
	}
}

bool CharClassBuilder::contains(char c) {
	return ranges_.find(CharRange(c, c)) != end();
}

void CharClassBuilder::negate() {
	std::vector<CharRange> v;
	v.reserve(ranges_.size() + 1);

	iterator it = begin();
	if(it == end()) {
		v.push_back(CharRange(0, CHAR_MAX));
	} else {
		int next_lo = 0;
		if(it->lo == 0) {
			next_lo = it->hi + 1;
			it++;
		}
		for(; it != end(); it++) {
			v.push_back(CharRange(next_lo, it->lo-1));
			next_lo = it->hi + 1;
		}
		if(next_lo <= CHAR_MAX) {
			v.push_back(CharRange(next_lo, CHAR_MAX));
		}
	}

	ranges_.clear();
	for(auto chrange: v) {
		ranges_.insert(chrange);
	}

	nchars_ = CHAR_MAX+1 - nchars_;
}

CharClassBuilder* CharClassBuilder::intersect(CharClassBuilder *cc) {
	CharClassBuilder* new_cc = new CharClassBuilder();
	for(iterator it1 = cc->begin(); it1 != cc->end(); it1++) {
		iterator it2 = ranges_.lower_bound(*it1); // lowest range that overlaps
		if (it2 != end()) {
			for(; it2 != ranges_.upper_bound(*it1); it2++) {
				char lo = std::max(it2->lo, it1->lo);
				char hi = std::min(it2->hi, it1->hi);
				new_cc->add_range(lo, hi);
			}
		}
	}
	return new_cc;
}

CharClassBuilder* CharClassBuilder::set_minus(CharClassBuilder *cc) {
	// Set minus is just the intersection with the complement;
	cc->negate();

	CharClassBuilder* new_cc = intersect(cc);

	cc->negate();

	return new_cc;
}

// std::ostream& operator<<(std::ostream &os, CharClassBuilder const &b) {
// 	for(auto &range: b.ranges_) {
// 		os << '[' << (int)range.lo << ',' << (int)range.hi << ']';
// 	}
// 	return os;
// }

bool CharClassBuilder::operator==(const CharClassBuilder& rhs) const {
	return ranges_ == rhs.ranges_;
}


std::unique_ptr<CharClass> CharClassBuilder::get_charclass() {
	auto cc = std::make_unique<CharClass>(static_cast<int>(ranges_.size()));
	cc->nchars_ = nchars_;
	int n = 0;
	for(iterator it=begin(); it != end(); it++) {
		cc->ranges_[n++] = *it;
	}
	cc->nranges_ = n;
	return cc;
}

CharClass::~CharClass() {
	delete [] ranges_;
}

bool CharClass::contains(char a) {
	CharRange* range = ranges_;
	int n = nranges_;

	while(n > 0) {
		int m = n/2;
		if(range[m].hi < a) {
			range += m+1;
			n -= m+1;
		} else if (a < range[m].lo) {
			n = m;
		} else { // range[m].lo <= a && a <= range[m].hi
			return true;
		}
	}
	return false;
}

bool CharClass::operator<(const CharClass& cc) const {
	for(int i=0; i < std::min(nranges_, cc.nranges_); i++) {
		if(ranges_[i].lo < cc.ranges_[i].lo) return true;
		else if(ranges_[i].lo > cc.ranges_[i].lo) return false;
		else if(ranges_[i].hi < cc.ranges_[i].hi) return true;
		else if(ranges_[i].hi > cc.ranges_[i].hi) return false;
	}

	return nranges_ < cc.nranges_;
}


std::ostream& operator<<(std::ostream &os, CharClassBuilder const &cc) {
	if(cc.is_dot()) return os << '.';
	else if(cc.nchars_ == 1) return os << (char)cc.ranges_.begin()->lo;
	os << "[";
	for(auto &range: cc.ranges_) {
		if(range.lo == range.hi)
			os << (char)range.lo;
		else
			os << (char)range.lo << '-' << (char)range.hi;
	}
	os << "]";
	return os;
}

} // end namespace rematch
