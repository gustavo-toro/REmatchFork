#include "filter_factory_visitor.hpp"

#include "factories/factories.hpp"

namespace visitors {

regex2filters :: regex2filters() {
	m_filterFactory = new FilterFactory();
}

FilterFactory& regex2filters :: operator()(ast::altern const &a) {
	for(auto &elem: a) {
		(*this)(elem);
	}
	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::concat const &c) {
	for(auto &elem: c) {
		(*this)(elem);
	}

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::iter const &it) {
	(*this)(it.expr);

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::group const &g) {
	boost::apply_visitor(*this, g);

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::parenthesis const &p) {
	(*this)(p.root);

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::assignation const &a) {
	(*this)(a.root);

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::atom const &a) {
	boost::apply_visitor(*this, a);

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::charset const &cs) {
	m_filterFactory->addFilter(CharClass(cs));

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(char const &a) {
	m_filterFactory->addFilter(CharClass(a));

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::anychar const &a) {
	m_filterFactory->addFilter(CharClass(ANYCHAR, false));

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::anydigit const &a) {
	m_filterFactory->addFilter(CharClass(ANYDIGIT, false));

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::nondigit const &a) {
	m_filterFactory->addFilter(CharClass(ANYDIGIT, true));

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::anyword const &a) {
	m_filterFactory->addFilter(CharClass(ANYWORD, false));

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::nonword const &a)  {
	m_filterFactory->addFilter(CharClass(ANYWORD, true));

	return *m_filterFactory;
}

FilterFactory& regex2filters :: operator()(ast::anywhitespace const &a)  {
	m_filterFactory->addFilter(CharClass(ANYSPACE, false));

	return *m_filterFactory;
}

} // end namespace visitors