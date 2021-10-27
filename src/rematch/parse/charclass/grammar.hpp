// #define BOOST_SPIRIT_DEBUG
#ifndef SRC_REMATCH_PARSE_CHARCLASS_GRAMMAR_HPP
#define SRC_REMATCH_PARSE_CHARCLASS_GRAMMAR_HPP

#ifndef BOOST_SPIRIT_USE_PHOENIX_V3
  #define BOOST_SPIRIT_USE_PHOENIX_V3
#endif

#ifndef BOOST_SPIRIT_UNICODE
  #define BOOST_SPIRIT_UNICODE
#endif

// Prevent ambiguity from Boost's placeholders
#ifndef BOOST_BIND_NO_PLACEHOLDERS
  #define BOOST_BIND_NO_PLACEHOLDERS
#endif

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include "parse/charclass/ast.hpp"

namespace rematch {

namespace qi  = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
// namespace unicode = boost::spirit::unicode;

template <typename It>
struct CharClassParser : qi::grammar<It, ast::atom()> {

  CharClassParser() : CharClassParser::base_type(charclass_) {
    using qi::lexeme;
    using qi::lit;
    using ascii::char_;
    using ascii::alpha;
    using ascii::alnum;
    using ascii::no_case;
    using qi::attr;
    using qi::uint_;
    using qi::hex;
    using qi::eps;
    using qi::eol;
    using qi::omit;
    using qi::matches;

    using phoenix::construct;
    using phoenix::val;

    using namespace qi::labels;

    charclass_ =  charset_ | special_ | symb_ ;

    special_ = lit(".")[_val = ast::special(SpecialCode::kAnyChar, true)]           |
               lit("\\d")[_val = ast::special(SpecialCode::kAnyDigit, true)]        |
               lit("\\D")[_val = ast::special(SpecialCode::kAnyDigit, false)]       |
               lit("\\w")[_val = ast::special(SpecialCode::kAnyWord, true)]         |
               lit("\\W")[_val = ast::special(SpecialCode::kAnyWord, false)]        |
               lit("\\s")[_val = ast::special(SpecialCode::kAnyWhiteSpace, true)]   |
               lit("\\S")[_val = ast::special(SpecialCode::kAnyWhiteSpace, false)];

    symb_ = (unesc_char_ |
            "\\" >> char_("\\+*?(){}[]|!.-") |
            ~char_("\\+*?(){}[]|.") // Anything but '+*?(){}[]|.'
            );

    // Inside a charclass is not necesary to escape some symbols (e.g. ".")
    charclass_symb_ = (unesc_char_|
                      charclass_unesc_char_ |
                      ~char_("\\[]")
                      );

    charset_ = '['
              >> ('^' >> attr(true) | attr(false))
              >> +(range_ | charclass_symb_) >>
              ']';

    range_ = charclass_symb_ >> '-' >> charclass_symb_;

    unesc_char_.add("\\a", '\a')("\\f", '\f')("\\n", '\n')
              ("\\r", '\r')("\\t", '\t')("\\v", '\v')("\\\\", '\\')
              ("\\\"", '"')("\\0", (char)0);

    charclass_unesc_char_.add("\\.", '.')("\\+", '+')("\\*", '*')("\\?", '?')
                          ("\\)", ')')("\\)", ')')("\\}", '}')("\\{", '{')
                          ("\\|", '|')("\\^", '^')("\\]", ']')("\\[", '[')
                          ("\\!", '!');
} // end RegexParser (Constructor)

 private:
  qi::rule<It, ast::atom()> charclass_;
  qi::rule<It, ast::assignation()> assign_;
  qi::rule<It, ast::charset()> charset_;
  qi::rule<It, char()> symb_;
  qi::rule<It, char()> charclass_symb_;
  qi::rule<It, ast::charset::range()> range_;
  qi::rule<It, ast::special()> special_;

  qi::symbols<char const, char const> unesc_char_;
  qi::symbols<char const, char const> charclass_unesc_char_;
};

} // end namespace rematch


#endif // SRC_REMATCH_PARSE_CHARCLASS_GRAMMAR_HPP
