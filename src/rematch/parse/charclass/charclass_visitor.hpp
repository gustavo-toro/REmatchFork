#ifndef SRC_REMATCH_PARSE_CHARCLASS_CHARCLASS_VISITOR_HPP
#define SRC_REMATCH_PARSE_CHARCLASS_CHARCLASS_VISITOR_HPP

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#include "charclass.hpp"
#include "parse/regex/ast.hpp"

namespace rematch {
namespace visitors {

struct charclass_visitor : boost::static_visitor<CharClassBuilder> {
	CharClassBuilder operator()(ast::atom const &a) const;
	CharClassBuilder operator()(ast::charset const &cs) const;
	CharClassBuilder operator()(char const &a) const;
	CharClassBuilder operator()(ast::special const &a) const;
};

} // end namespace visitors
} // end namespace rematch

#endif // SRC_REMATCH_PARSE_CHARCLASS_CHARCLASS_VISITOR_HPP
