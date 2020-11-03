#ifndef EVALITER_HPP
#define EVALITER_HPP

#include "match.hpp"

namespace rematch {

class Evaluator;

class EvaluatorIter {
 public:
  EvaluatorIter() = default;
  EvaluatorIter(Evaluator* eval);

  Match_ptr next();

 private:
  Evaluator* eval_;
}; // end class EvaluatorIter

} // end namespace rematch

#endif // EVALITER_HPP