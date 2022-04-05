#include "match.hpp"

#include <memory>
#include <sstream>

#include "evaluation/document/strdocument.hpp"

namespace rematch {

Span Match::span(std::string var) const {
  try {
    int pos = var_factory_->position(var);
    // TODO: change empty return
    if (data_[pos].empty()) return std::make_pair(-3, -3);
    return std::make_pair(data_[pos][0], data_[pos][1]);
  } catch (...) {
    throw std::logic_error("No mapping assigned to variable.");
  }
}

std::string Match::group(std::string var, std::shared_ptr<StrDocument>& doc) const {
  try {
    int pos = var_factory_->position(var);
    // TODO: change empty return
    if (data_[pos].empty()) return "";
    return doc->substring(data_[pos][0], data_[pos][1]);
  } catch (...) {
    throw std::logic_error("No mapping assigned to variable.");
  }
}

std::vector<std::string> Match::variables() const {
  return var_factory_->variables();
}

std::string Match::pprint(std::shared_ptr<StrDocument>& doc) const {
  std::stringstream ss;
  for (size_t i = 0; i < data_.size(); i++) {
    ss << var_factory_->get_var(i) << " =";
    for (size_t j = 0; j < data_[i].size() / 2; j++) {
      ss << " \""
         << doc->substring(data_[i][2 * j], data_[i][2 * j + 1])
         << "\"";
    }
  }
  return ss.str();
}

std::ostream& operator<<(std::ostream& os, Match& m) {
  for (size_t i = 0; i < m.data_.size(); i++) {
    os << m.var_factory_->get_var(i) << " =";
    for (size_t j = 0; j < m.data_[i].size() / 2; j++) {
      os << " |"
         << m.data_[i][2 * j]
         << ','
         << m.data_[i][2 * j + 1]
         << '>';
    }
    os << '\n';
  }
  return os;
}

}  // end namespace rematch