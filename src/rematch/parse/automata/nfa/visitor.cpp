#include "visitor.hpp"

#include "parse/automata/nfa/ast.hpp"
#include "automata/nfa/lva.hpp"
#include "automata/nfa/state.hpp"
#include "factories/factories.hpp"
#include "charclass.hpp"

#include "parse/regex/ast.hpp"
#include "parse/charclass/charclass_visitor.hpp"

#include <iostream>
#include <bitset>

namespace rematch {

// File to automata visitor
file_to_automata :: file_to_automata() {
    automata = new rematch::LogicalVA();
}

rematch::State *file_to_automata::get_state(std::string state_name) {
    if (!states_map.count(state_name)) {
        rematch::State* state = new rematch::State();
        states_map[state_name] = state;
        automata->states.push_back(state);
    }
    return states_map.at(state_name);
}

std::bitset<32> file_to_automata::get_variable_code(automata::variable const &variable) {
    if (!automata->varFactory()->contains(variable.name)) {
        automata->varFactory()->add(variable.name);
    }
    if (variable.is_opening) {
        return automata->varFactory()->open_code(variable.name);
    }
    return automata->varFactory()->close_code(variable.name);
}

int file_to_automata::get_filter_code(ast::atom const &a) {
  rematch::CharClassBuilder charclass = boost::apply_visitor(visitors::charclass_visitor(), a);
  if (!automata->filterFactory()->contains(charclass)) {
      automata->filterFactory()->add_filter(charclass);
  }
  return automata->filterFactory()->get_code(charclass);
}

// Case 1: char transition
void file_to_automata :: operator()(automata::char_transition const &ct) {
    rematch::State *from_state = get_state(ct.from_state);
    rematch::State *to_state = get_state(ct.to_state);
    int filter_code = get_filter_code(ct.text);
    from_state->addFilter(filter_code, to_state);
}

// Case 2: variable transition
void file_to_automata :: operator()(automata::variable_transition const &vt) {
    rematch::State *from_state = get_state(vt.from_state);
    rematch::State *to_state = get_state(vt.to_state);

    std::bitset<32> bitset_code;
    for (automata::variable const &variable : vt.variables) {
        bitset_code |= get_variable_code(variable);
    }
    from_state->addCapture(bitset_code, to_state);
}

// Case 3: epsilon transition
void file_to_automata :: operator()(automata::epsilon_transition const &et) {
    rematch::State *from_state = get_state(et.from_state);
    rematch::State *to_state = get_state(et.to_state);
    from_state->addEpsilon(to_state);
}

// Case 4: initial state
void file_to_automata :: operator()(automata::initial_state const &is) {
    rematch::State *state = get_state(is.state);
    automata->set_initial(state);
}

// Case 5: final state
void file_to_automata :: operator()(automata::final_state const &fs) {
    rematch::State *state = get_state(fs.state);
    state->setFinal(true);
    automata->finalStates.push_back(state);
}

} // end namespace rematch