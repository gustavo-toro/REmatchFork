#ifndef STRUCTS__MATCH__SPAN_ITERATOR_HPP
#define STRUCTS__MATCH__SPAN_ITERATOR_HPP

#include <bitset>
#include <map>
#include <utility>

namespace rematch {

using Span = std::pair<int64_t, int64_t>;
using MatchData = std::map<int64_t, std::bitset<32>>;

class SpanIterator {
  public:
    SpanIterator(const MatchData* d, int i);
    Span* next();
  private:
    const MatchData* data;
    int pos;
    MatchData::const_iterator it;
}; // end class SpanIterator

} // end namespace rematch

#endif // STRUCTS__MATCH__SPAN_ITERATOR_HPP