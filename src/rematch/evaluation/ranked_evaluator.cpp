#include "ranked_evaluator.hpp"

#include "automata/dfa/detstate.hpp"
#include "memmanager.hpp"
#include "util/timer.hpp"

#define	FORCE_INLINE inline __attribute__((always_inline))

namespace rematch {
namespace ranked {

RankedEvaluator::RankedEvaluator(WeightedVA &wVA, std::shared_ptr<Document> d)
    : automaton_(wVA),
      text_(d)  {
  init(); // Initialize the automaton for the first time.
}

void RankedEvaluator::init() {

}

Match_ptr RankedEvaluator::next() {

}

} // end namespace ranked
} // end namespace rematch