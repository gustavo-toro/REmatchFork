#include "stringiterator.hpp"

#include <iostream>

namespace rematch {

StringIterator::StringIterator(SpanIterator it, std::shared_ptr<StrDocument>& doc)
  : s_iter(it), document(doc) { }

std::string* StringIterator::next() {
  for(auto s = s_iter.next(); s != nullptr; s = s_iter.next()) {
    std::string* ret(new std::string(document->substring(s->first, s->second)));
    return ret;
  }
  return nullptr;
}

} // end namespace rematch