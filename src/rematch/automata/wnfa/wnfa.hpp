#ifndef AUTOMATA_WNFA_HPP
#define AUTOMATA_WNFA_HPP

#include <bitset>
#include <vector>


namespace rematch {
namespace ranked {

class State;

// Abstract base class for state transitions.
class Transition {
 public:
  virtual State* next() const = 0;
  virtual State* prev() const = 0;
  virtual double weight() const = 0;
}; // end class Transition


// A Filter transition (a transition that consumes input).
class Filter : public Transition {
 public:
  Filter(State* p, uint c, double w, State* n)
      : next_(n), prev_(p), code_(c), weight_(w) {}
  virtual State* next() const { return next_; }
  virtual State* prev() const { return prev_; }
  virtual double weight() const { return weight_; }
  unsigned int code() const { return code_; }
 private:
  State* next_;
  State* prev_;
  unsigned int code_;
  double weight_;

}; // end class Filter


// A Capture transition (a transition that opens/closes a set of variables)
class Capture : public Transition {
 public:

  Capture(State* p, std::bitset<32> b, double w, State* n)
      : next_(n), prev_(p), code_(b), weight_(w) {}
  virtual State* next() const { return next_; }
  virtual State* prev() const { return prev_; }
  virtual double weight() const { return weight_;  }
  std::bitset<32> code() const { return code_; }

 private:

  State* next_;
  State* prev_;
  std::bitset<32> code_;
  double weight_;
}; // end class Capture


class State {
 public:
  State() = default;

  Filter& add_filter(uint code, double weight, State* next) {
    return filters_.emplace_back(this, code, weight, next);
  }
  Capture& add_capture(std::bitset<32> code, double weight, State* next) {
    return captures_.emplace_back(this, code, weight, next);
  }

  // Given a filter code, return the subset of reached states
  std::vector<State*> next_filter(unsigned int code) const;
  // Given a variable code, return the subset of reached states
  std::vector<State*> next_capture(std::bitset<32> code) const;

  unsigned int id_; // State unique id

 private:
  static const unsigned int ID = 0;

  std::vector<Filter> filters_;
  std::vector<Capture> captures_;

}; // end class State

class WeightedVA {
 public:
  std::vector<State*> states_;
  std::vector<State*> accepting_states_;
 private:
  std::vector<State> prt_states_; // States are allocated here
}; // end class WeightedVA



} // end namespace ranked
} // end namespace rematch



#endif // AUTOMATA_WNFA_HPP

