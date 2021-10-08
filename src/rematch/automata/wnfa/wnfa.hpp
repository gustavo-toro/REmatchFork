#ifndef AUTOMATA_WNFA_HPP
#define AUTOMATA_WNFA_HPP

#include <bitset>
#include <vector>
#include <random>

#include "structs/how/how.hpp"

#include "structs/capture_place.hpp"


namespace rematch {
namespace ranked {

class RankedEvaluator;

template<typename T = CapturePlace, typename G = double>
class WeightedVA {
 public:

  class State;
  friend RankedEvaluator;

  class State {
   public:

    friend RankedEvaluator;
    // Abstract base class for state transitions.
    class Transition {
     public:
      virtual State* next() const = 0;
      virtual State* prev() const = 0;
      virtual G weight() const = 0;
      virtual bool captures() const = 0;
      virtual ulong code() const = 0;

      virtual void set_weight(G w) = 0;
    }; // end class Transition

    // A Filter transition (a transition that consumes input).
    class Filter : public Transition {
     public:
      Filter(State* p, uint c, G w, State* n)
          : next_(n), prev_(p), code_(c), weight_(w) {}
      virtual State* next() const { return next_; }
      virtual State* prev() const { return prev_; }
      virtual G weight() const { return weight_; }
      virtual bool captures() const { return false; }
      virtual ulong code() const { return code_; }

      virtual void set_weight(G w) { weight_ = w; }

     private:

      State* next_;
      State* prev_;
      ulong code_;
      G weight_;

    }; // end class Filter

    // A Capture transition (a transition that opens/closes a set of variables)
    class Capture : public Transition {
     public:

      Capture(State* p, std::bitset<32> b, G w, State* n)
          : next_(n), prev_(p), code_(b), weight_(w) {}

      // Virtual getters
      virtual State* next() const { return next_; }
      virtual State* prev() const { return prev_; }
      virtual G weight() const { return weight_;  }
      virtual ulong code() const { return code_.to_ulong(); }

      // Always returns true, as a Capture captures output
      virtual bool captures() const { return true; }

      virtual void set_weight(G w) { weight_ = w; }

     private:

      State* next_;
      State* prev_;
      std::bitset<32> code_;
      G weight_;
    }; // end class Capture

    State() = default;

    Filter& add_filter(uint code, G weight, State* next) {
      Filter *f = new Filter(this, code, weight, next);
      transitions_.push_back(f);
      return *f;
    }

    Capture& add_capture(std::bitset<32> code, G weight, State* next) {
      Capture *c = new Capture(this, code, weight, next);
      transitions_.push_back(c);
      return *c;
    }

    // Given a filter code, return the subset of reached states
    std::vector<State*> next_filter(unsigned int code) const;
    // Given a variable code, return the subset of reached states
    std::vector<State*> next_capture(std::bitset<32> code) const;

    unsigned int id_; // State unique id

  private:
    static const unsigned int ID = 0;

    std::vector<State::Transition*> transitions_;

    // Used at evaluation to store the iteration when the state was last visited
    int visited_at_ = -1;

    bool initial_;
    G intial_weight_;

    bool accepting_;
    G accepting_weight_;

    HeapOfWords<T,G> *heap_;
    HeapOfWords<T,G> *old_heap_;

  }; // end class State

  // Getters
  std::vector<State*>& states() { return states_; }
  std::vector<State*>& accepting_states() { return accepting_states_; }

  // Sets random a weight to every transition in the automaton's graph.
  // It uses a uniform distribution between a lower and upper bound.
  void set_random_weights(double lw_bound, double up_bound) {

    std::uniform_real_distribution<double> unif(lw_bound, up_bound); // distribution
    std::default_random_engine rng;

    for(State* p: states_) {
      for(auto& t: p->transitions_) {
        t->set_weight(unif(rng));
      }
    }

    // Set the initial weight
    init_weight_ = unif(rng);

    // Set the final weights
    for(State* qf: accepting_states_) {
      qf->accepting_weight_ = unif(rng);
    }
  }

 private:
  std::vector<State*> states_;
  std::vector<State*> accepting_states_;

  State* init_state_;
  G init_weight_;
}; // end class WeightedVA


} // end namespace ranked
} // end namespace rematch



#endif // AUTOMATA_WNFA_HPP

