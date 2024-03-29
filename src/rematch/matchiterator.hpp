#ifndef MATCHITERATOR_HPP
#define MATCHITERATOR_HPP

#include <iterator>

#include "match.hpp"
// #include "eval.hpp"
// #include "enumerator"

namespace rematch {

class Evaluator;
struct EvalStats;

class MatchIterator {
public:
  MatchIterator() = default;
  MatchIterator(Evaluator *e, EvalStats *s);

  Match_ptr next() const;

  Evaluator *evaluator_;
  EvalStats *stats_;
}; // end class MatchIterator

} // end namespace rematch

#endif // MATCHITERATOR_HPP
