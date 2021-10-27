#include "visitor.hpp"

#include "parse/automata/wva/ast.hpp"
#include "automata/wnfa/wnfa.hpp"
#include "factories/factories.hpp"
#include "charclass.hpp"

#include "parse/regex/ast.hpp"
#include "parse/charclass/charclass_visitor.hpp"

#include <iostream>
#include <bitset>

namespace rematch {

// File to automata visitor
wVAvisitor::wVAvisitor() : automata(new ranked::WeightedVA<>()) {}

ranked::WeightedVA<>::State* wVAvisitor::get_state(std::string state_name) {
    if (!states_map.count(state_name)) {
        auto* state = automata->create_state(std::stoi(state_name));
        states_map[state_name] = state;
    }
    return states_map.at(state_name);
}

std::bitset<32> wVAvisitor::get_variable_code(ast::wva::variable const &variable) {
    if (!automata->vfactory()->contains(variable.name))
        automata->vfactory()->add(variable.name);
    if (variable.type == ast::wva::CaptureType::kOpen)
        return automata->vfactory()->open_code(variable.name);
    return automata->vfactory()->close_code(variable.name);
}

int wVAvisitor::get_filter_code(ast::atom const &a) {
  rematch::CharClassBuilder charclass = boost::apply_visitor(visitors::charclass_visitor(), a);
  if (!automata->ffactory()->contains(charclass)) {
      automata->ffactory()->add_filter(charclass);
  }
  return automata->ffactory()->get_code(charclass);
}

void wVAvisitor::operator()(ast::wva::weighted_transition const &ct) {
    auto *from_state = get_state(ct.from_state);
    auto *to_state = get_state(ct.to_state);
    int filter_code = get_filter_code(ct.text);
    std::bitset<32> bitset_code;
    for (auto const &variable : ct.variables) {
        bitset_code |= get_variable_code(variable);
    }

    from_state->add_transition(filter_code, bitset_code, ct.weight, to_state);
}

void wVAvisitor::operator()(ast::wva::state const &s) {
    auto *state = get_state(s.label);

    if(s.type == rematch::ast::wva::StateType::kInit) {
        state->set_initial(true);
        state->set_initial_weight(s.weight);
        automata->set_initial_state(state);
    } else {
        state->set_accepting(true);
        state->set_accepting_weight(s.weight);
        automata->add_accepting_state(state);
    }
}


} // end namespace rematch