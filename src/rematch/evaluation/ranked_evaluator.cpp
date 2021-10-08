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
  q0->old_heap_ = new HoW();
  q0->old_heap_->add({0,-1}, automaton_.init_weight_);

  current_states_.clear();
  current_states_.push_back(q0);
}

Match_ptr RankedEvaluator::next() {
  if(!finished_preprocessing_) {
    preprocessing();
    finished_preprocessing_ = true;
  }

  return enumerate();
}

void RankedEvaluator::preprocessing() {
  for(; i_pos_ < text_.size(); ++i_pos_) {
    for(wVA::State *p: current_states_) {
      for(wVA::State::Transition *t : p->transitions_) {
        wVA::State* q = t->next(); // next state
        auto &h = p->old_heap_;
        if(t->captures()) {
          h = h->extend_by({t->code(), i_pos_});
        }
        h = h->increase_by(t->weight());
        q->heap_ = q->heap_->meld_with(h);

        if(q->visited_at_ < i_pos_) {
          q->visited_at_ = i_pos_;
          new_states_.push_back(q);
        }
      }
    }
    current_states_.swap(new_states_);
  }

  for(auto &q: current_states_) {
    if(q->accepting_) {
      auto *h = q->heap_->increase_by(q->accepting_weight_);
      h_out_->meld_with(h);
    }
  }
}

Match_ptr RankedEvaluator::enumerate() {
  if(!h_out_->empty()) {
    auto word = h_out_->find_min();
    h_out_ = h_out_->delete_min();

    return std::make_unique<Match>(word);
  }
  return nullptr;
}

} // end namespace ranked
} // end namespace rematch