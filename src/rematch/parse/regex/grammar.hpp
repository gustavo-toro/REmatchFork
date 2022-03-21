// #define BOOST_SPIRIT_DEBUG
#ifndef SRC_REMATCH_PARSE_REGEX_GRAMMAR_HPP
#define SRC_REMATCH_PARSE_REGEX_GRAMMAR_HPP

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
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/object.hpp>

#include "parse/regex/ast.hpp"
#include "parse/charclass/grammar.hpp"

namespace rematch {

namespace qi  = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
namespace unicode = boost::spirit::unicode;

template <typename It> // It : Iterator type
struct RegexParser : qi::grammar<It, ast::altern()> {

  RegexParser() : RegexParser::base_type(altern_) {
    using qi::lexeme;
    using qi::lit;
    using unicode::char_;
    using unicode::alpha;
    using unicode::alnum;
    using unicode::no_case;
    using qi::attr;
    using qi::uint_;
    using qi::hex;
    using qi::eps;
    using qi::eol;
    using qi::omit;
    using qi::matches;

    using qi::_1;
    using qi::_2;
    using qi::_3;
    using qi::_4;

    using qi::on_error;
    using qi::fail;
    using qi::debug;

    using phoenix::construct;
    using phoenix::val;

    using namespace qi::labels;

    /////////////////////////
    ////  GRAMMAR RULES  ////
    /////////////////////////

    altern_ = concat_ % '|';

    concat_ = +(iter_);

    iter_ = group_ >> *rep_;

    rep_ = lit('?')[_val = ast::repetition(0,1)] |
            lit('*')[_val = ast::repetition(0,-1)] |
            lit('+')[_val = ast::repetition(1,-1)] |
            ('{' >> uint_ >> '}')[_val = construct<ast::repetition>(_1,_1)]  |
            ("{," >> uint_ >> '}')[_val = construct<ast::repetition>(0,_1)]  |
            ('{' >> uint_ >> ",}" ) [_val = construct<ast::repetition>(_1,-1)] |
            ('{' >> uint_ >> ',' >> uint_ >> '}')[_val = construct<ast::repetition>(_1,_2)];

    group_ =  parenthesis_ | assign_ | charclass_ ;

    parenthesis_ =  '(' >> altern_ >> ')';

    assign_ =   '!' >> var_  >> '{' >> altern_ >> '}';

    var_ = alpha >> *(alnum);

    // Rule naming (for debugging)

    altern_.name("alternation");
    concat_.name("concatenation");
    iter_.name("iteration");
    group_.name("group");
    parenthesis_.name("parenthesis");
    rep_.name("repetition");
    var_.name("variable");

    /////////////////////
    ////  DEBUGGING  ////
    /////////////////////


    on_error<fail>(altern_,
      std::cout << phoenix::val("Error! Expecting ")
                << boost::spirit::_4                   // what failed?
                << phoenix::val(" here: \"")
                << construct<std::string>(boost::spirit::_3, boost::spirit::_2)   // iterators to error-pos, end
                << phoenix::val("\"")
                << std::endl
     );

    // debug(altern_);
    // debug(concat_);
    // debug(iter_);
    // debug(group_);
    // debug(parenthesis_);
    // debug(rep_);
    // debug(var_);

} // end RegexParser (Constructor)

 private:
  // Rule declaration

  qi::rule<It, ast::altern()> altern_;
  qi::rule<It, ast::concat()> concat_;
  qi::rule<It, ast::iter()> iter_;
  qi::rule<It, ast::group()> group_;
  qi::rule<It, ast::parenthesis()> parenthesis_;
  qi::rule<It, ast::repetition()> rep_;
  qi::rule<It, std::string()> var_;
  qi::rule<It, ast::assignation()> assign_;

  CharClassParser<It> charclass_;
};

} // end namespace rematch


#endif // SRC_REMATCH_PARSE_REGEX_GRAMMAR_HPP
