#ifndef AUTOMATA_NFA_UDFA_HPP
#define AUTOMATA_NFA_UDFA_HPP

#include <optional>
#include <vector>

#include "automata/nfa/state.hpp"
#include "automata/dfa/dstate.hpp"
#include "automata/abs_dstate.hpp"

namespace rematch {

struct StateSubset {
  StateSubset(size_t nfa_size) : bitset(nfa_size, false) {}

  void add(LogicalVA::State* q) {
    if(!bitset[q->id]) {
      subset.push_back(q);
      bitset[q->id] = true;
    }
  }

  std::vector<LogicalVA::State*> subset;
  std::vector<bool> bitset;

}; // end struct StateSubset

class UDFA {
 public:
  static size_t const SIZE_THRESHOLD = 1;

  class State: public abstract::DState {
   public:
    friend class UDFA;

    State(LogicalVA::State *s)
        : id_(s->id), initial_(s->initial()), accepting_(s->accepting()) {
      states_subset_.push_back(s);
    }

    State(std::vector<LogicalVA::State*> s)
        : initial_(true), accepting_(false), states_subset_(s) {
      for(LogicalVA::State *q: states_subset_) {
        if(!q->initial()) initial_ = false;
        if(q->accepting()) accepting_ = true;
      }
    }

    std::optional<Transition> next_transition(char a) const override {
      return transitions_[a];
    };

    ECS::Node *node() const override { return node_; }
    void set_node(ECS::Node *n) override { node_ = n; }

    int visited() const override { return visited_; }
    void set_visited(int n) override { visited_ = n; }

    bool accepting() const override { return accepting_; }

    bool initial() const override { return initial_; }

   protected:

    int id_{-1};

    std::array<std::optional<Transition>, 128> transitions_;

    bool initial_{false};
    bool accepting_{false};

    int visited_{-1};

    ECS::Node *node_{nullptr};

    std::vector<LogicalVA::State*> states_subset_;

  }; // end class UDFA::State

  using CaptureStatesTable = std::vector<std::pair<State*, std::bitset<32>>>;

  UDFA(ExtendedVA const &A, size_t sz_thres=SIZE_THRESHOLD);

  UDFA() = delete;

  State* init_state() { return initial_state_; }

  CaptureStatesTable init_eval_states() { return init_eval_states_; }

  Transition next_transition(abstract::DState *q, char a);

  size_t size() const { return states_.size(); }

 private:

  // Search for corresponding dstate. If alloc is true then the state will be
  // allocated and returned. Else returns nullptr
  std::vector<State*> obtain_states(StateSubset const &ss);

  State* obtain_state(LogicalVA::State *q);

  size_t nfa_size_;

  State* initial_state_;

  std::vector<State*> states_;
  std::vector<Transition*> transitions_;

  std::shared_ptr<FilterFactory> ffactory_;

  std::unordered_map<std::vector<bool>, State*> dstate_map_;

  size_t size_threshold_;

  CaptureStatesTable init_eval_states_;
}; // end class UDFA

} // end namespace rematch

namespace std {

template<>
struct hash<rematch::StateSubset> {
  size_t operator()(const rematch::StateSubset &ss) const {
    return std::hash<std::vector<bool>>{}(ss.bitset);
  }
};

} // end namespace std

#endif // AUTOMATA_NFA_UDFA_HPP
