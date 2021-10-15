
#ifndef GRAMMAR_AUTOMATA_HPP
#define GRAMMAR_AUTOMATA_HPP

#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include "ast.hpp"

#include "parse/regex/ast.hpp"

namespace rematch {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template <typename Iterator>
struct automata_parser : qi::grammar<Iterator, rematch::automata::any(), ascii::space_type> {
    automata_parser() : automata_parser::base_type(start) {
        using qi::lit;
        using ascii::char_;
        using qi::_val;

        using boost::phoenix::val;

        special_chars_rule.add("\\a", '\a')("\\b", '\b')("\\f", '\f')
                              ("\\n", '\n')("\\r", '\r')("\\t", '\t')
                              ("\\v", '\v')("\\\\", '\\');

        // Single caracter (i.e "a" or "0" or "&" or "\n" or "\t" or "\\", but not [TAB] or "\")
        single_char_rule = special_chars_rule | qi::graph - char_("\\");

        range_rule =
            char_("a-z") >> lit("-") >> char_("a-z")
            | char_("A-Z") >> lit("-") >> char_("A-Z")
            | char_("0-9") >> lit("-") >> char_("0-9");

        charset_rule =            // Set of character as in regex (i.e [a-zA-Z0-9] or [agk] or [^g-z] or [ \t\n\r])
            lit('[')
            >> -char_('^')
            >> +(range_rule | (single_char_rule - char_("]")) | char_(" "))
            >> lit(']')
            ;

        // Set of characters that are represented by special codes
        special_ = lit(".")[_val = ast::special(SpecialCode::kAnyChar, true)]       |
               lit("\\d")[_val = ast::special(SpecialCode::kAnyDigit, true)]        |
               lit("\\D")[_val = ast::special(SpecialCode::kAnyDigit, false)]       |
               lit("\\w")[_val = ast::special(SpecialCode::kAnyWord, true)]         |
               lit("\\W")[_val = ast::special(SpecialCode::kAnyWord, false)]        |
               lit("\\s")[_val = ast::special(SpecialCode::kAnyWhiteSpace, true)]   |
               lit("\\S")[_val = ast::special(SpecialCode::kAnyWhiteSpace, false)];

        charclass_rule =          // Any single char or set of chars
            charset_rule
            | special_
            | single_char_rule
            ;

        state_rule = +char_("a-zA-Z0-9,");

        opening_variable_rule =
            lit('<')
            >> +char_("a-zA-Z0-9")
            >> qi::attr(true)
            ;

        closing_variable_rule =
            +char_("a-zA-Z0-9")
            >> lit('>')
            >> qi::attr(false)
            ;

        variable_set_rule =
            (opening_variable_rule | closing_variable_rule)
            % lit(',')
            ;

        char_transition_rule =
            lit('t')
            >> state_rule
            >> charclass_rule
            >> state_rule
            ;

        epsilon_transition_rule =
            lit('e')
            >> state_rule
            >> state_rule
            ;

        variable_transition_rule =
            lit('v')
            >> state_rule
            >> variable_set_rule
            >> state_rule
            ;

        initial_state_rule =
            lit('i')
            >> state_rule
            ;

        final_state_rule =
            lit('f')
            >> state_rule
            ;

        start =
            char_transition_rule
            | variable_transition_rule
            | epsilon_transition_rule
            | initial_state_rule
            | final_state_rule
            ;
    }

    private:

    // Lexemes
    qi::symbols<char, char> special_chars_rule;
    qi::rule<Iterator, ast::special()> special_;
    qi::rule<Iterator, char()> single_char_rule;
    qi::rule<Iterator, automata::charset()> charset_rule;
    qi::rule<Iterator, automata::charclass()> charclass_rule;
    qi::rule<Iterator, automata::range()> range_rule;
    qi::rule<Iterator, std::string()> state_rule;
    qi::rule<Iterator, automata::variable()> opening_variable_rule;
    qi::rule<Iterator, automata::variable()> closing_variable_rule;
    qi::rule<Iterator, std::vector<automata::variable>()> variable_set_rule;

    // Rules with space skipper
    qi::rule<Iterator, automata::char_transition(), ascii::space_type> char_transition_rule;
    qi::rule<Iterator, automata::variable_transition(), ascii::space_type> variable_transition_rule;
    qi::rule<Iterator, automata::epsilon_transition(), ascii::space_type> epsilon_transition_rule;
    qi::rule<Iterator, automata::initial_state(), ascii::space_type> initial_state_rule;
    qi::rule<Iterator, automata::final_state(), ascii::space_type> final_state_rule;
    qi::rule<Iterator, automata::any(), ascii::space_type> start;
};

} // end namespace rematch

#endif