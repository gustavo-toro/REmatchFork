#include "evaliter.hpp"

#include "eval.hpp"
#include "match.hpp"

namespace rematch {

EvaluatorIter::EvaluatorIter(Evaluator* eval): eval_(eval) {}

Match_ptr EvaluatorIter::next() {return eval_->next();}

} // end namespace rematch