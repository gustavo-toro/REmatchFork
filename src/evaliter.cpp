#include "evaliter.hpp"

#include "eval.hpp"
#include "match.hpp"

namespace rematch {

EvaluatorIter::EvaluatorIter(Evaluator* eval): eval_(eval) {
}

Match EvaluatorIter::next() {
  return eval_->next();
}

bool EvaluatorIter::hasNext() {
  return eval_->hasNext();
}

} // end namespace rematch