#ifndef AST_AUTOMATA_HPP
#define AST_AUTOMATA_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/optional.hpp>

#include <string>

#include <set>
#include <vector>
#include <string>

#include "parse/regex/ast.hpp"


namespace rematch {

namespace automata {
    typedef boost::tuple<char, char> range;

    struct charset
    {
        using element = boost::variant<char, range>;
        boost::optional<char> negated;
        std::set<element> elements;
    };

    typedef boost::variant<
        charset,
        rematch::ast::special,
        char
    > charclass;

    struct variable {
        std::string name;
        bool is_opening;
    };

    struct char_transition {
        std::string from_state;
        charclass text;
        std::string to_state;
    };

    struct variable_transition
    {
        std::string from_state;
        std::vector<variable> variables;
        std::string to_state;
    };

    struct epsilon_transition
    {
        std::string from_state;
        std::string to_state;
    };

    struct initial_state
    {
        std::string state;
    };

    struct final_state
    {
        std::string state;
    };

    typedef boost::variant<
        char_transition,
        variable_transition,
        epsilon_transition,
        initial_state,
        final_state
    > any;
}

} // end namespace rematch

// We need to tell fusion about our structs
// to make them a first-class fusion. This has to
// be in global scope.

BOOST_FUSION_ADAPT_STRUCT(
    rematch::automata::charset,
    (boost::optional<char>, negated)
    (std::set<rematch::automata::charset::element>, elements)
)

BOOST_FUSION_ADAPT_STRUCT(
    rematch::automata::variable,
    (std::string, name)
    (bool, is_opening)
)

BOOST_FUSION_ADAPT_STRUCT(
    rematch::automata::char_transition,
    (std::string, from_state)
    (rematch::automata::charclass, text)
    (std::string, to_state)
)

BOOST_FUSION_ADAPT_STRUCT(
    rematch::automata::variable_transition,
    (std::string, from_state)
    (std::vector<rematch::automata::variable>, variables)
    (std::string, to_state)
)

BOOST_FUSION_ADAPT_STRUCT(
    rematch::automata::epsilon_transition,
    (std::string, from_state)
    (std::string, to_state)
)

BOOST_FUSION_ADAPT_STRUCT(
    rematch::automata::initial_state,
    (std::string, state)
)

BOOST_FUSION_ADAPT_STRUCT(
    rematch::automata::final_state,
    (std::string, state)
)

#endif