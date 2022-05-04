#include "dstate.hpp"

#include <algorithm>

#include "automata/nfa/state.hpp"

namespace rematch {

int DState::ID = 0;

DState::DState(size_t tot_states)
  : id_(ID++),
    transitions_(128),
    states_bitmap_(tot_states, false) {}

DState::DState(size_t tot_states, std::vector<State*> states)
    : id_(ID++),
      transitions_(128),
      states_bitmap_(tot_states, false),
      states_subset_(states) {
  for(auto &p: states_subset_) {
    states_bitmap_[p->id] = true;
    if(p->accepting())
      flags_ |= kAcceptingState;
  }
}

DState::DState(size_t tot_states, std::set<State*> states)
    : id_(ID++),
      transitions_(128),
      states_bitmap_(tot_states, false),
      states_subset_(states.begin(), states.end()) {
  for(auto &p: states_subset_) {
    states_bitmap_[p->id] = true;
    if(p->accepting())
      flags_ |= kAcceptingState;
  }
}

void DState::add_state(State* p) {
  auto lower = std::lower_bound(states_subset_.begin(), states_subset_.end(), p,
    [](const State* s1, const State* s2) { return s1->id < s2->id; }
  );

  if(lower == states_subset_.end() || (*lower)->id != p->id) {
    states_subset_.insert(lower, p);
    states_bitmap_[p->id] = true;
  }
}

void DState::add_direct(char a, DState* q) {
  if(transitions_[a] == nullptr)
    transitions_[a] = std::make_unique<Transition>(q);
  else
    transitions_[a]->add_direct(q);
}

void DState::add_capture(char a, std::bitset<32> S, DState* q) {
  if(transitions_[a] == nullptr)
    transitions_[a] = std::make_unique<Transition>(new DCapture(S, q));
  else
    transitions_[a]->add_capture(new DCapture(S, q));
}

void DState::add_empty(char a) {
  transitions_[a] = std::make_unique<Transition>();
}

void DState::set_accepting(bool b) {
  if(b)
    flags_ |= Flags::kAcceptingState;
  else
    flags_ &= ~Flags::kAcceptingState;
}

void DState::set_initial(bool b) {
  if(b)
    flags_ |= Flags::kInitialState;
  else
    flags_ &= ~Flags::kInitialState;
}

void DState::pass_node(internal::ECS::Node* n) {
  node = n;
  ++n->ref_count_;
}

} // end namespace rematch