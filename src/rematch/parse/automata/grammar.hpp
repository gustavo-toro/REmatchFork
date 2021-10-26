
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
struct automata_parser : qi::grammar<Iterator, rematch::automata::any(), ascii::space_type> {
    automata_parser() : automata_parser::base_type(start) {
        using qi::lit;
        using ascii::char_;
        using qi::_val;

        using boost::phoenix::val;

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
    CharClassParser<Iterator> charclass_rule;
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

#endif // SRC_REMATCH_PARSE_AUTOMATA_GRAMMAR_HPP
