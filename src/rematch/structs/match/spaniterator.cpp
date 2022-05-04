#include "spaniterator.hpp"

namespace rematch {

SpanIterator::SpanIterator(const MatchData* d, int i)
  : data(d), pos(i) { 
    it = data->begin();
  }

Span* SpanIterator::next() {
  int64_t open = -1;
  while (it != data->end()) {
    // Closing variable
    if (it->second[2*pos + 1] && open != -1) {
      Span* ret(new Span(open, it->first));
      return ret;
    }
    // Opening variable
    if (it->second[2*pos]) {
      open = it->first;
    }
    it++;
  }
  return nullptr;
}

} // end namespace rematch