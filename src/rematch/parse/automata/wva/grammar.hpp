
#ifndef SRC_REMATCH_PARSE_AUTOMATA_GRAMMAR_HPP
#define SRC_REMATCH_PARSE_AUTOMATA_GRAMMAR_HPP

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include "ast.hpp"

#include "parse/regex/ast.hpp"
#include "parse/charclass/grammar.hpp"

namespace rematch {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct wva_parser : qi::grammar<Iterator, rematch::ast::wva::any(), ascii::space_type> {
    wva_parser() : wva_parser::base_type(start) {
        using qi::lit;
        using ascii::char_;
        using qi::_val;
        using qi::attr;
        using qi::double_;

        using boost::phoenix::val;

        state_rule = +char_("a-zA-Z0-9,");

        opening_variable_rule =
            +char_("a-zA-Z0-9")
            >> lit('<')
            >> qi::attr(ast::wva::CaptureType::kOpen)
            ;

        closing_variable_rule =
            lit('>')
            >> +char_("a-zA-Z0-9")
            >> qi::attr(ast::wva::CaptureType::kClose)
            ;

        variable_set_rule =
            *(opening_variable_rule | closing_variable_rule)
            ;

        weighted_transition_rule =
            lit('t')
            >> state_rule
            >> '{' >> charclass_rule >> '|'
            >> '(' >> variable_set_rule >> ')'
            >> ('|' >> double_ | attr(0.0))
            >> '}'
            >> state_rule
            ;

        initial_state_rule =
            lit('i')
            >> state_rule >> attr(ast::wva::StateType::kInit)
            >> ('{' >> double_ >> '}'| attr(0.0))
            ;

        final_state_rule =
            lit('f')
            >> state_rule >> attr(ast::wva::StateType::kAccepting)
            >> ('{' >> double_ >> '}'| attr(0.0))
            ;

        start =
              weighted_transition_rule |
              (initial_state_rule | final_state_rule)
            ;
    }

    private:

    // Lexemes
    CharClassParser<Iterator> charclass_rule;
    qi::rule<Iterator, std::string()> state_rule;
    qi::rule<Iterator, ast::wva::variable()> opening_variable_rule;
    qi::rule<Iterator, ast::wva::variable()> closing_variable_rule;
    qi::rule<Iterator, std::vector<ast::wva::variable>()> variable_set_rule;
    // Rules with space skipper
    qi::rule<Iterator, ast::wva::state(), ascii::space_type> initial_state_rule;
    qi::rule<Iterator, ast::wva::state(), ascii::space_type> final_state_rule;
    qi::rule<Iterator, ast::wva::weighted_transition(), ascii::space_type> weighted_transition_rule;

    qi::rule<Iterator, ast::wva::any(), ascii::space_type> start;
};

} // end namespace rematch

#endif // SRC_REMATCH_PARSE_AUTOMATA_GRAMMAR_HPP
