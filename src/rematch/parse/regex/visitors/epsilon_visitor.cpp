#include "epsilon_visitor.hpp"

#include "parse/regex/exceptions.hpp"
#include "parse/regex/ast.hpp"

namespace rematch {
namespace visitors {

bool regex_epsilon::operator()(ast::altern const &node) const {
	// if any member has epsilon is enough
	for (auto c : node) 
		if ((*this)(c)) return true;
	return false;
}

bool regex_epsilon::operator()(ast::concat const &c) const {
	// all members must have epsilon
	for (auto it : c) 
		if (!(*this)(it)) return false;
	return true;
}

bool regex_epsilon::operator()(ast::iter const &it) const {
	// if any repetition has size zero is enough
	for (auto rep : it.repetitions)
		if (rep.start_ == 0) return true;		
	// if expr has epsilon is enough
	if ((*this)(it.expr)) return true;
	return false;
}

bool regex_epsilon::operator()(ast::group const &g) const {
	return boost::apply_visitor(*this, g);
}

bool regex_epsilon::operator()(ast::parenthesis const &p) const {
	return (*this)(p.root);
}

bool regex_epsilon::operator()(ast::assignation const &a) const {
	auto root = (*this)(a.root);
	// if capture has epsilon, the program must stop
	if (root) throw parsing::BadRegex("Regex contains 'epsilon' in its language.");
	return false;
}

bool regex_epsilon::operator()(ast::atom const &a) const {
	return false;
}

}
}