#include "match.hpp"

#include <memory>
#include <sstream>

#include "evaluation/document/strdocument.hpp"

namespace rematch {

SpanIterator Match::spans(std::string var) const {
  int pos = var_factory_->position(var);
  SpanIterator s_iter = SpanIterator(data, pos, it_lower, it_upper);
  return s_iter;
}

Span* Match::span(std::string var) const {
  SpanIterator s_iter = spans(var);
  Span* s = s_iter.next();
  return s;
}

Match_ptr Match::submatch(Span* s) const {
  Match_ptr ret(new Match(var_factory_, data, data->lower_bound(s->first), data->upper_bound(s->second)));
  return ret;
}

StringIterator Match::groups(std::string var, std::shared_ptr<StrDocument>& doc) const {
  SpanIterator s_iter = spans(var);
  StringIterator g_iter = StringIterator(s_iter, doc);
  return g_iter;
}

std::string* Match::group(std::string var, std::shared_ptr<StrDocument>& doc) const {
  StringIterator g_iter = groups(var, doc);
  std::string* g = g_iter.next();
  return g;
}

std::vector<std::string> Match::variables() const {
  return var_factory_->variables();
}

std::string Match::pprint(std::shared_ptr<StrDocument>& doc) const {
  std::stringstream ss;
  for (size_t i = 0; i < var_factory_->size(); i++) {
    std::string var = var_factory_->get_var(i);
    StringIterator g_iter = groups(var, doc);
    ss << var << " =";
    for (auto g = g_iter.next(); g != nullptr; g = g_iter.next()) {
      ss << " \"" << *g << '\"';
    }
    ss << std::endl;
  }
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, Match& m) {
  for (size_t i = 0; i < m.var_factory_->size(); i++) {
    std::string var = m.var_factory_->get_var(i);
    SpanIterator s_iter = m.spans(var);
    os << var << " =";
    for (auto s = s_iter.next(); s != nullptr; s = s_iter.next()) {
      os << " |" << s->first << ',' << s->second << '>';
    }
    os << std::endl;
  }
  return os;
}

}  // end namespace rematch