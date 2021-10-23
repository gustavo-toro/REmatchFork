#include "match.hpp"

namespace rematch {

Match::operator bool() const {
  for (auto d : data_)
    if (!d.empty()) return true;
  return false;
};

std::vector<std::string> Match::variables() const {
  return var_factory_->variables();
};

SpanVec Match::spans(std::string var) const {
  try {
    SpanVec ret;
    int pos = var_factory_->position(var);
    for (size_t i = 0; i < data_[pos].size() / 2; ++i)
      ret.push_back(std::make_pair(data_[pos][2 * i], data_[pos][2 * i + 1]));
    return ret;
  } catch (...) {
    throw std::logic_error("No mapping assigned to variable.");
  }
};

std::string Match::pprint(std::shared_ptr<StrDocument>& doc) const {
  std::stringstream ss;
  ss << "not implemented.";
  return ss.str();
};

std::ostream& operator<<(std::ostream& os, Match& m) {
  for (size_t i = 0; i < m.data_.size(); ++i) {
    os << m.var_factory_->get_var(i)
       << " =";
    for (size_t j = 0; j < m.data_[i].size() / 2; ++j) {
      os << " |"
         << m.data_[i][2 * j]
         << ','
         << m.data_[i][2 * j + 1]
         << ">";
    }
    os << '\n';
  }
  return os;
};

}  // namespace rematch