#ifndef SRC_REMATCH_AUTOMATA_WNFA_WNFA_HPP
#define SRC_REMATCH_AUTOMATA_WNFA_WNFA_HPP

#include <bitset>
#include <vector>
#include <random>
#include <unordered_map>
#include <deque>

#include "automata/nfa/state.hpp"
#include "automata/nfa/lva.hpp"
#include "structs/how/how.hpp"
#include "structs/how/how_paper.hpp"
#include "structs/capture_place.hpp"
#include "charclass.hpp"
#include "factories/factories.hpp"

namespace rematch {
namespace ranked {

class RankedEvaluator;
class wVAvisitor;

template<typename T = CapturePlace, typename G = double>
class WeightedVA {
 public:
  friend RankedEvaluator;
  friend wVAvisitor;

  class State {
   public:

    friend RankedEvaluator;
    friend WeightedVA<T,G>;

    // A Filter transition (a transition that consumes input).
    class Transition {
     public:
      Transition(State* p, State* n, G w, uint c, capture_t X=0)
          : next_(n), prev_(p), S_(X), code_(c), weight_(w) {}

      State* next() const { return next_; }
      State* prev() const { return prev_; }

      uint code() const { return code_; }
      capture_t S() const { return S_; }

      G weight() const { return weight_; }
      void set_weight(G w) { weight_ = w; }

     private:

      State* next_;           // next state
      State* prev_;           // previous state

      capture_t S_;               // all captures
      uint code_;            // the filter code

      G weight_;   // the weight
    }; // end class Filter

    State() = default;

    State(std::shared_ptr<FilterFactory> ff, uint id) : id_(id), ffact_(ff) {}

    void set_accepting(bool b) { accepting_ = b; }
    bool accepting() const { return accepting_;  }

    void set_initial(bool b) { initial_ = b; }
    bool initial() const { return initial_; }

    void set_visited_at(long n) { visited_at_ = n; }
    long visited_at() const { return visited_at_; }

    G initial_weight() const { return initial_weight_; }
    void set_initial_weight(G w) { initial_weight_ = w; }

    G accepting_weight() const { return accepting_weight_; }
    void set_accepting_weight(G w) { accepting_weight_ = w; }

    std::vector<Transition*> transitions() const { return transitions_; }

    std::vector<Transition*> next_transitions(char a) const {
      typename std::vector<IntervalMap>::const_iterator it, first, last;
      typename std::vector<IntervalMap>::difference_type count, step;

      first = tmap_.begin();
      last = tmap_.end();

      count = std::distance(first, last);

      while(count > 0) {
        it = first;
        step = count / 2;
        std::advance(it, step);
        if(it->hi < a) {
          first = ++it;
          count -= step + 1;
        } else if(a < it->lo) {
          count = step;
        } else {
          return it->transitions;
        }
      }
      return std::vector<Transition*>();
    }

    Transition& add_transition(uint code, capture_t S, G weight, State* next) {
      Transition *t = new Transition(this, next, weight, code, S);
      transitions_.push_back(t);
      update_transition_map(t);
      return *t;
    }

    unsigned int id_; // State unique id

  private:

    struct IntervalMap {
      int lo;
      int hi;
      std::vector<Transition*> transitions;

      IntervalMap(int l, int h, std::vector<Transition*> t=std::vector<Transition*>())
        : lo(l), hi(h), transitions(t) {}

      friend bool operator<(const IntervalMap& lhs, const IntervalMap& rhs) {
        return lhs.hi < rhs.lo;
      }
    };

    void update_transition_map(Transition* t) {
      CharClassBuilder ccb = ffact_->get_filter(t->code());
      for(auto range = ccb.begin(); range != ccb.end(); ++range) {
        int hi = range->hi, lo = range->lo;
        // Look for an inmediate range to the left of [lo, hi]. If exists
        // then erase and extend [lo, hi] accordingly
        if(lo > 0) {
          auto it = std::lower_bound(tmap_.begin(), tmap_.end(), IntervalMap(lo, lo));
          if(it != tmap_.end() && lo >= it->lo && it->lo < it->hi) {
            int it_lo = it->lo, it_hi = it->hi;
            it->lo = lo+1;
            it = tmap_.emplace(it, it_lo, lo, it->transitions);
            ++it; // Move iterator to the element pushed to the right
            if(hi < it->hi) {
              it->hi = hi;
              auto place = std::lower_bound(it, tmap_.end(), IntervalMap(hi+1, it_hi));
              tmap_.emplace(place, hi+1, it_hi, it->transitions);
            }
          }
        }
        // Look for an inmediate range to the right of [lo, hi]. If exists
        // then erase and extend [lo, hi] accordingly
        if(hi < RUNE_MAX) {
          auto it = std::lower_bound(tmap_.begin(), tmap_.end(), IntervalMap(hi, hi));
          if(it != tmap_.end() && hi >= it->lo && it->lo < it->hi) {
            int it_hi = it->hi;
            it->hi = hi;
            tmap_.emplace(it+1, hi+1, it_hi, it->transitions);
            // Not necesary to check for lo. Did it in previous step.
          }
        }

        // Search for ranges inside [lo, hi]. Erase them.
        // The remaining ranges that overlap with [lo, hi] must be inside
        // it.
        auto it = std::lower_bound(tmap_.begin(), tmap_.end(), IntervalMap(lo, hi));
        for(;;) {
          if(it == tmap_.end() || hi < it->lo) {
            tmap_.emplace(it, lo, hi, std::vector(1, t));
            break;
          }
          if(lo < it->lo) {
            int it_lo = it->lo;
            lo = it_lo;
            it = tmap_.emplace(it, lo, it_lo-1, std::vector(1, t));
          } else { // then lo == it->lo
            it->transitions.push_back(t);
            if(it->hi == hi)
              break;
            lo = it->hi + 1;
          }
          ++it;
        }
      }
    }

    std::vector<State::Transition*> transitions_;

    std::vector<IntervalMap> tmap_;

    // Used at evaluation to store the iteration when the state was last visited
    long visited_at_ = -1;

    bool initial_ = false;
    G initial_weight_;

    bool accepting_ = false;
    G accepting_weight_;

    HoWPaper<T,G> *heap_ = new HoWPaper<T,G>();
    HoWPaper<T,G> *old_heap_ = new HoWPaper<T,G>();

    std::shared_ptr<FilterFactory> ffact_;
  }; // end class State

  WeightedVA()
      : ffact_(std::make_shared<FilterFactory>()),
        vfact_(std::make_shared<VariableFactory>()) {
  }

  WeightedVA(const LogicalVA &A)
      : ffact_(A.filterFactory()), vfact_(A.varFactory()) {
    std::unordered_map<rematch::State*, State*> states_table;

    for(auto &q_old: A.states) {
      State* q_new = new State(ffact_, q_old->id);
      states_table[q_old] = q_new;
      states_.push_back(q_new);
      if(q_old->isFinal)
        accepting_states_.push_back(q_new);
    }

    for(auto &q_old: A.states) {
      State* q_new = states_table[q_old];

      q_new->set_accepting(q_old->isFinal);
      q_new->set_initial(q_old->isInit);

      for(auto &filt: q_old->filters) {
        if(filt->next->filters.size() > 0 || filt->next->captures.size() == 0) {
          q_new->add_transition(filt->code, 0, 0, states_table[filt->next]);
        }
        for(auto &capt: filt->next->captures) {
          q_new->add_transition(filt->code, capt->code, 0, states_table[capt->next]);
        }
      }
    }

    // Deal with the initial state
    init_state_ = new State(ffact_, states_.size());
    if(A.initState()->filters.size() > 0)
      init_state_->add_transition(0, 0, 0, states_table[A.initState()]);
    for(auto &capt: A.initState()->captures)
      init_state_->add_transition(0, capt->code, 0, states_table[capt->next]);

    fix_reachable_states();
  };

  // Getters
  std::vector<State*>& states() { return states_; }
  std::vector<State*>& accepting_states() { return accepting_states_; }
  std::shared_ptr<VariableFactory> vfactory() const { return vfact_; }
  std::shared_ptr<FilterFactory> ffactory() const { return ffact_; }

  State* create_state(uint id) {
    auto* p = new State(ffact_, id);
    states_.push_back(p);
    return p;
  }

  void add_accepting_state(State* p) { accepting_states_.push_back(p); }
  void set_initial_state(State* p) { init_state_ = p; }

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
    init_state_->initial_weight_ = init_weight_;

    // Set the final weights
    for(State* qf: accepting_states_) {
      qf->accepting_weight_ = unif(rng);
    }
  }

  friend std::ostream& operator<<(std::ostream &os, const WeightedVA<T,G> &A) {
    for(auto& p: A.states_) {
      p->set_visited_at(-1);
    }

    std::deque<State*> queue;

    queue.push_back(A.init_state_);
    A.init_state_->set_visited_at(0);

    while(!queue.empty()) {
      State* p = queue.front();
      queue.pop_front();

      for(auto &t : p->transitions()) {
        os << "t " << t->prev()->id_                   << " {"
                   << A.ffact_->get_filter(t->code())  << "|("
                   << A.vfact_->print_varset(t->S())   << ")|"
                   << t->weight()                       << "} "
                   << t->next()->id_                   << '\n';

        if(t->next()->visited_at() < 0) {
          t->next()->set_visited_at(0);
          queue.push_back(t->next());
        }
      } // end for
    } // end while

    for(auto& pf: A.accepting_states_) {
      os << "f " << pf->id_ << " {" << pf->accepting_weight() << "}\n";
    }

    os << "i " << A.init_state_->id_ << " {" << A.init_state_->initial_weight() << "}\n";

    return os;
  }

 private:

  // Resets the states_ and accepting_states_ vectors to only the states that
  // are reachable from the initial state.
  void fix_reachable_states() {
    for(auto& p: states_) {
      p->visited_at_ = -1;
    }

    std::deque<State*> queue;

    queue.push_back(init_state_);
    init_state_->visited_at_ = 0;


    std::vector<State*> n_states, n_accepting_states;

    while(!queue.empty()) {
      State* p = queue.front();
      queue.pop_front();

      p->visited_at_ = 1;
      n_states.push_back(p);
      if(p->accepting_)
        n_accepting_states.push_back(p);

      for(auto &t:  p->transitions_) {
        if(t->next()->visited_at_ < 0) {
          t->next()->visited_at_ = 0;
          queue.push_back(t->next());
        }
      }
    }

    states_.swap(n_states);
    accepting_states_.swap(n_accepting_states);

  };
  std::vector<State*> states_;
  std::vector<State*> accepting_states_;

  State* init_state_;
  G init_weight_;

  std::shared_ptr<FilterFactory> ffact_;
  std::shared_ptr<VariableFactory> vfact_;
}; // end class WeightedVA

} // end namespace ranked
} // end namespace rematch

#endif // SRC_REMATCH_AUTOMATA_WNFA_WNFA_HPP

