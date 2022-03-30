#include "match.hpp"

namespace rematch {

Match::operator bool() const {
	for (auto d : data_)
		if (!d.empty()) return true;
	return false;
}

std::vector<std::string> Match::variables() const {
	return var_factory_->variables();
}

SpanVec Match::spans(std::string var) const {
	SpanVec ret;
	int pos = var_factory_->position(var);
	for (size_t i = 0; i < data_[pos].size() / 2; ++i)
		ret.push_back(std::make_pair(data_[pos][2 * i], data_[pos][2 * i + 1]));
	return ret;
}

boost::optional<Span> Match::span(std::string var) const {
	int pos = var_factory_->position(var);
	if (data_[pos].empty()) return boost::none;
	return std::make_pair(data_[pos][0], data_[pos][1]);
}

StrVec Match::groups(std::string var, std::shared_ptr<StrDocument>& doc) const {
	StrVec ret;
	int pos = var_factory_->position(var);
	for (size_t i = 0; i < data_[pos].size() / 2; ++i)
		ret.push_back(doc->substring(data_[pos][2 * i], data_[pos][2 * i + 1]));
	return ret;
}

boost::optional<std::string> Match::group(std::string var, std::shared_ptr<StrDocument>& doc) const {
	int pos = var_factory_->position(var);
	if (data_[pos].empty()) return boost::none;
	return doc->substring(data_[pos][0], data_[pos][1]);
}

std::string Match::pprint(std::shared_ptr<StrDocument>& doc) const {
	std::stringstream ss;

	for (size_t i = 0; i < data_.size(); ++i) {
		std::string var = var_factory_->get_var(i);
		ss << var << " = ";
		for (auto sub : groups(var, doc))
			ss << '\"' << sub << "\" ";
		ss << '\n';
	}
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, Match& m) {
	for (size_t i = 0; i < m.data_.size(); ++i) {
		os << m.var_factory_->get_var(i)
			 << " =";
		for (size_t j = 0; j < m.data_[i].size() / 2; ++j) {
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

}  // namespace rematch