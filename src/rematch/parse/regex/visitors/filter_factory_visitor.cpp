#include "filter_factory_visitor.hpp"

#include "factories/factories.hpp"
#include "parse/charclass/charclass_visitor.hpp"

namespace rematch {
namespace visitors {

regex2filters::regex2filters() {
	filter_factory_ = std::make_unique<FilterFactory>();
	charclass_visitor_ = charclass_visitor();
}

ff_ptr regex2filters::get_factory() {
	return std::move(filter_factory_);
}

void regex2filters::operator()(ast::altern const &a) {
	for(auto &elem: a)
		(*this)(elem);
}

void regex2filters::operator()(ast::concat const &c) {
	for(auto &elem: c) {
		(*this)(elem);
	}
}

void regex2filters::operator()(ast::iter const &it) {
	(*this)(it.expr);
}

void regex2filters::operator()(ast::group const &g) {
	boost::apply_visitor(*this, g);
}

void regex2filters::operator()(ast::parenthesis const &p) {
	(*this)(p.root);
}

void regex2filters::operator()(ast::assignation const &a) {
	(*this)(a.root);
}

void regex2filters::operator()(ast::atom const &a) {
	filter_factory_->add_filter(boost::apply_visitor(charclass_visitor_, a));
}

} // end namespace visitors
} // end namespace rematch