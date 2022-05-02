#ifndef SPAN_ITERATOR_HPP
#define SPAN_ITERATOR_HPP

#include "match.hpp"

namespace rematch {

class SpanIterator {
  public:
    SpanIterator(const MatchData* d, int i);
    Span* next();
  private:
    const MatchData* ordered_data;
    int pos;
    MatchData::const_iterator it;
}; // end class SpanIterator

} // end namespace rematch

#endif // SPAN_ITERATOR_HPP