#include "segment_identification/search_variable_set_automaton/nfa/search_nfa.hpp"

#include <iostream>
#include <map>

#include "parsing/charclass.hpp"

namespace rematch {

SearchVA::SearchVA(LogicalVA const &A) {
  LogicalVA A_prim(A); // Make a copy of the automaton

  A_prim.remove_captures();

  A_prim.remove_epsilon();

  A_prim.trim();

  A_prim.relabel_states();

  #ifndef NDEBUG
  std::cout << "SearchVA:\n" << A_prim << "\n\n";
  #endif


  std::map<unsigned int, SearchNFAState*> logical_va_state_id_to_search_nfa_state;
  for (LogicalVAState *logical_va_state : A_prim.states) {
    states.push_back(new SearchNFAState(logical_va_state));
    logical_va_state_id_to_search_nfa_state
      [logical_va_state->id] = states.back();
  }

  for (LogicalVAState *logical_va_state : A_prim.states) {
    SearchNFAState *initial_state =
      logical_va_state_id_to_search_nfa_state[logical_va_state->id];
    for (LogicalVAFilter *logical_va_filter : logical_va_state->filters) {
      CharClass charclass = logical_va_filter->charclass;
      SearchNFAState *next =
        logical_va_state_id_to_search_nfa_state
          [logical_va_filter->next->id];
      initial_state->add_filter(charclass, next);
    }
  }

  initial_state_ =
    logical_va_state_id_to_search_nfa_state[A_prim.initial_state()->id];
  accepting_state_ =
    logical_va_state_id_to_search_nfa_state[A_prim.accepting_state()->id];
}

// ---  Getters  ---  //

std::vector<SearchNFAState*> const & SearchVA::get_states() const { return states; }

SearchNFAState* SearchVA::initial_state() const { return initial_state_; }

SearchNFAState* SearchVA::accepting_state() const { return accepting_state_; }



} // end namespace rematch
