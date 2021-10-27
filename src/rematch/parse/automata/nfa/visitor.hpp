#ifndef SRC_REMATCH_PARSE_AUTOMATA_VISITOR_HPP
#define SRC_REMATCH_PARSE_AUTOMATA_VISITOR_HPP

#include "automata/nfa/lva.hpp"
#include "charclass.hpp"

#include "parse/automata/nfa/ast.hpp"
#include "parse/regex/ast.hpp"

#include <bitset>
#include <unordered_map>

#include "parse/charclass/ast.hpp"

namespace rematch {

struct file_to_automata : boost::static_visitor<void>
{
    // LVA to be returned
    LogicalVA *automata;

    // Hash table between state names and state references
    std::unordered_map<std::string, rematch::State*> states_map;

    // Constructor
    file_to_automata();

    // Internal methods
    rematch::State *get_state(std::string state_name);
    std::bitset<32> get_variable_code(automata::variable const &variable);
    int get_filter_code(ast::atom const &a);

    // Case 1: char transition
    void operator()(automata::char_transition const &ct);
    // Case 2: variable transition
    void operator()(automata::variable_transition const &vt);
    // Case 3: epsilon transition
    void operator()(automata::epsilon_transition const &et);
    // Case 4: initial state
    void operator()(automata::initial_state const &is);
    // Case 5: final state
    void operator()(automata::final_state const &fs);
};

} // end namespace rematch

#endif // SRC_REMATCH_PARSE_AUTOMATA_VISITOR_HPP
