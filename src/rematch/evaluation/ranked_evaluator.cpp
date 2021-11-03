#include "ranked_evaluator.hpp"

#include "structs/how/how_paper.hpp"

#define	FORCE_INLINE inline __attribute__((always_inline))

namespace rematch {
namespace ranked {

// Syntactic sugar
using HoW = HoWPaper<CapturePlace, double>;
using wVA = WeightedVA<>;

RankedEvaluator::RankedEvaluator(wVA &wVA, const std::string &d)
    : automaton_(wVA),
      text_(d)  {
  init(); // Initialize the automaton for the first time.
}

void RankedEvaluator::init() {
  for(wVA::State* p: automaton_.states()) {
    p->visited_at_ = -1;
  }

  wVA::State* q0 = automaton_.init_state_;
  q0->heap_ = q0->heap_->add(kBottomCapture, automaton_.init_weight_);

  current_states_.clear();
  current_states_.push_back(q0);

  read(0, -1);
}

Match_ptr RankedEvaluator::next() {
  if(!finished_preprocessing_) {
    preprocessing();
    finished_preprocessing_ = true;
  }

  return enumerate();
}

void RankedEvaluator::preprocessing() {
  char a;
  for(; i_pos_ < text_.size(); ++i_pos_) {
    a = text_[i_pos_] & 0x7F; // Only ASCII
    read(a, i_pos_);
  }

  for(auto &q: current_states_) {
    if(q->accepting_) {
      auto *h = q->heap_->increase_by(q->accepting_weight_);
      h_out_ = h_out_->meld_with(h);
    }
  }
}

void RankedEvaluator::read(char a, long pos) {
  new_states_.clear();
  for(wVA::State *p: current_states_) {
    for(auto &t: p->next_transitions(a)) {
      wVA::State* q = t->next(); // next state

      auto h = p->heap_;

      if (p->visited_at_ >= pos+1) // If visited already
        h = p->old_heap_; // Then we need the old heap;

      if(t->S() != 0)
        h = h->extend_by({t->S(), pos+1});

      h = h->increase_by(t->weight());

      if(q->visited_at_ < pos+1) {
        q->visited_at_ = pos+1;
        q->old_heap_ = q->heap_;
        q->heap_ = new HoW();
        new_states_.push_back(q);
      }

      q->heap_ = q->heap_->meld_with(h);
    }
  }
  current_states_.swap(new_states_);
}

Match_ptr RankedEvaluator::enumerate() {
  if(!h_out_->empty()) {
    std::list<CapturePlace> word = h_out_->find_min();
    auto minprio = h_out_->min_prio();
    h_out_ = h_out_->delete_min();

    return std::make_unique<Match>(automaton_.vfact_, word, minprio);
  }
  return nullptr;
}

} // end namespace ranked
} // end namespace rematch