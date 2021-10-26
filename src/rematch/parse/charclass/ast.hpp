#ifndef PARSE__CHARCLASS__AST_HPP
#define PARSE__CHARCLASS__AST_HPP

#include <set>
#include <tuple>

#include <boost/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


namespace rematch {

// Codes for special charclasses (e.g. ".", "\d", "\W")
enum class SpecialCode {
  kNoSpecial = 0,
  kAnyChar,          // .
  kAnyDigit,         // \d
  kAnyWord,          // \w
  kAnyWhiteSpace,    // \s
};

namespace ast {

struct charset {
  /* Struct for class of char information containment */

  bool negated;  // Is a negated charset ?

  using range = std::tuple<char, char>;
  using element = boost::variant<char, range>;

  std::set<element> elements;
}; // end struct charset

// Special charclasses (e.g. ".", "\d", "\W")
struct special {
  special() = default;

  special(SpecialCode c, bool not_negated)
    : code(c), not_negated(not_negated) {}

  SpecialCode code;
  bool not_negated;
}; // end struct special


using atom = boost::variant<charset, char, special>;

} // end namespace ast
} // end namespace rematch

BOOST_FUSION_ADAPT_STRUCT(rematch::ast::charset,
  (bool, negated)
  (std::set<rematch::ast::charset::element>, elements))

#endif // PARSE__CHARCLASS__AST_HPP