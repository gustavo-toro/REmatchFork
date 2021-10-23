#include "match.hpp"

namespace rematch {

Match::operator bool() const {
  for (auto d : data_)
    if (!d.empty()) return true;
  return false;
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