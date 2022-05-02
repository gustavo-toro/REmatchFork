#include "spaniterator.hpp"

namespace rematch {

SpanIterator::SpanIterator(const MatchData* d, int i)
  : ordered_data(d), pos(i) { 
    it = ordered_data->begin();
  }

Span* SpanIterator::next() {
  int64_t open = -1;
  while (it != ordered_data->end()) {
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