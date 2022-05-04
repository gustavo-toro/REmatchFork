#ifndef STRUCTS__MATCH__SPAN_ITERATOR_HPP
#define STRUCTS__MATCH__SPAN_ITERATOR_HPP

#include <bitset>
#include <map>
#include <memory>
#include <utility>

namespace rematch {

using Span = std::pair<int64_t, int64_t>;
using MatchData = std::map<int64_t, std::bitset<32>>;

class SpanIterator {
  public:
    SpanIterator(const std::shared_ptr<MatchData> d, int i, MatchData::const_iterator s, MatchData::const_iterator e);
    Span* next();
  private:
    const std::shared_ptr<MatchData> data;
    int pos;
    MatchData::const_iterator it_lower;
    MatchData::const_iterator it_upper;
}; // end class SpanIterator

} // end namespace rematch

#endif // STRUCTS__MATCH__SPAN_ITERATOR_HPP