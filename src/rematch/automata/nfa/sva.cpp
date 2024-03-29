#include "sva.hpp"

#include <iostream>

#include "charclass.hpp"
#include "factories/factories.hpp"
#include "regex/regex_options.hpp"

namespace rematch {

SearchVA::SearchVA(LogicalVA const &A, Anchor a)
    : has_epsilon_(A.has_epsilon()), ffactory_(A.filterFactory()),
      vfactory_(A.varFactory()), anchor_(a) {
  LogicalVA A_prim(A); // Make a copy of the automaton

  A_prim.remove_captures();

  A_prim.remove_epsilon();

  A_prim.trim();

  A_prim.relabel_states();

#ifndef NDEBUG
  std::cout << "SearchVA:\n" << A_prim << "\n\n";
#endif

  states_.swap(A_prim.states);
  initial_state_ = A_prim.initial_state();
  accepting_state_ = A_prim.accepting_state();
}

// ---  Getters  ---  //

std::vector<LogicalVA::State*> const &SearchVA::states() const { return states_; }

LogicalVA::State *SearchVA::initial_state() const { return initial_state_; }

LogicalVA::State *SearchVA::accepting_state() const { return accepting_state_; }

bool SearchVA::has_epsilon() const { return has_epsilon_; }

} // end namespace rematch