#include "spaniterator.hpp"

namespace rematch {

SpanIterator::SpanIterator(
    const std::shared_ptr<MatchData> d,
    int i,
    MatchData::const_iterator s,
    MatchData::const_iterator e)
    : data(d), pos(i), it_lower(s), it_upper(e) {}

Span* SpanIterator::next() {
  int64_t open = -1;
  // while (it != data->end()) {
  while (it_lower != it_upper) {
    // Closing variable
    if (it_lower->second[2 * pos + 1] && open != -1) {
      Span* ret(new Span(open, it_lower->first));
      return ret;
    }
    // Opening variable
    if (it_lower->second[2 * pos]) {
      open = it_lower->first;
    }
    it_lower++;
  }
  return nullptr;
}

}  // end namespace rematch