#ifndef RANKED_EVALUATOR_HPP
#define RANKED_EVALUATOR_HPP

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <sstream>

#include "evaluation/evaluator.hpp"
#include "match.hpp"
#include "evaluation/document/document.hpp"

#include "automata/wnfa/wnfa.hpp"

namespace rematch {

namespace ranked {

class RankedEvaluator : public Evaluator {

 public:
  RankedEvaluator(WeightedVA& wva, std::shared_ptr<Document> d);

  virtual Match_ptr next();

 private:

  // Initialize the automaton and enumeration
  void init();

  WeightedVA& automaton_;

  std::shared_ptr<Document> text_;

  // Enumerator enumerator_;
}; // end class Evaluator

} // namespace ranked

} // namespace rematch

#endif // RANKED_EVALUATOR_HPP