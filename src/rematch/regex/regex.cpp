#include "regex.hpp"

#include "automata/nfa/lva.hpp"
#include "automata/nfa/sva.hpp"
#include "evaluation/evaluator.hpp"
#include "parse/parser.hpp"
#include "automata/nfa/udfa.hpp"

namespace rematch {

RegEx::RegEx(const std::string &pattern, rematch::RegExOptions rgx_opts)
    : pattern_(pattern), VA_(regex2LVA(pattern)), flags_(parseFlags(rgx_opts)) {
  vfactory_ = VA_->varFactory();
}

// Explicitly declared here for correct use of unique_ptr later
RegEx::~RegEx() {}

MatchIterator RegEx::find_iter(std::shared_ptr<Document> d, Anchor a) {
  std::shared_ptr<StrDocument> strd = std::static_pointer_cast<StrDocument>(d);
  eVA_ = std::make_shared<ExtendedVA>(*VA_, a);
  Evaluator *eval;
  EvalStats *stats = new EvalStats();
  if (flags_ & kSearching) {
    eval = new SegmentEvaluator(*this, strd, a, *stats);
  } else if(flags_ & kUnambiguous && !eVA_->is_ambiguous()) {
    eval = new NormalEvaluator<UDFA>(*this, strd, a, *stats);
  } else {
    eval = new BaseEvaluator(*this, strd, a, *stats);
  }
  return MatchIterator(eval, stats);
}

RegEx::flags_t RegEx::parseFlags(rematch::RegExOptions rgx_opts) {
  flags_t ret =
      rgx_opts.multi_line()   * kMultiLine    |
      rgx_opts.line_by_line() * kLineByLine   |
      rgx_opts.dot_nl()       * kDotNL        |
      rgx_opts.early_output() * kEarlyOutput  |
      rgx_opts.save_anchors() * kSaveAnchors  |
      rgx_opts.searching()    * kSearching    |
      rgx_opts.macrodfa()     * kMacroDFA     |
      rgx_opts.unambiguous()  * kUnambiguous;
  return ret;
}

} // end namespace rematch
