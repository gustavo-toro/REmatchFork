#ifndef PARSER__VISITORS__EPSILON_VISITOR
#define PARSER__VISITORS__EPSILON_VISITOR

#include "parse/regex/ast.hpp"

namespace rematch {
namespace visitors {

// true  -> the language CONTAINS epsilon
// false -> the language DOES NOT CONTAIN epsilon
struct regex_epsilon : boost::static_visitor<bool> {
  
	bool operator()(ast::altern const &a) const;
	bool operator()(ast::concat const &c) const;
	bool operator()(ast::iter const &it) const;
	bool operator()(ast::group const &g) const;
	bool operator()(ast::parenthesis const &p) const;
	bool operator()(ast::assignation const &a) const;
	bool operator()(ast::atom const &a) const;
};

}
} 

#endif