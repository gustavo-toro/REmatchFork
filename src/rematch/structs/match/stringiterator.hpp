#ifndef STRUCTS__MATCH__STRING_ITERATOR_HPP
#define STRUCTS__MATCH__STRING_ITERATOR_HPP

#include <memory>
#include <string>

#include "spaniterator.hpp"
#include "evaluation/document/strdocument.hpp"

namespace rematch {

using Span = std::pair<int64_t, int64_t>;

class StringIterator {
  public:
    StringIterator(SpanIterator it, std::shared_ptr<StrDocument>& doc);
    std::string* next();
  private:
    SpanIterator s_iter;
    std::shared_ptr<StrDocument>& document;
}; // end class StringIterator

} // end namespace rematch

#endif // STRUCTS__MATCH__STRING_ITERATOR_HPP