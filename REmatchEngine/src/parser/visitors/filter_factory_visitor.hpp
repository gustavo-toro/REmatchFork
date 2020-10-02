#ifndef PARSER__VISITORS__FILTER_FACTORY_VISITOR
#define PARSER__VISITORS__FILTER_FACTORY_VISITOR

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#include "factories/factories.hpp"

namespace visitors {

struct regex2filters : boost::static_visitor<FilterFactory&> {
	private:
		FilterFactory *m_filterFactory;
	public:
		regex2filters();

		FilterFactory &operator()(ast::altern const &a);
		FilterFactory &operator()(ast::concat const &c);
		FilterFactory &operator()(ast::iter const &it);
		FilterFactory &operator()(ast::group const &g);
		FilterFactory &operator()(ast::parenthesis const &p);
		FilterFactory &operator()(ast::assignation const &a);
		FilterFactory &operator()(ast::atom const &a);
		FilterFactory &operator()(ast::charset const &cs);
		FilterFactory &operator()(char const &a);
		FilterFactory &operator()(ast::anychar const &a);
		FilterFactory &operator()(ast::anydigit const &a);
		FilterFactory &operator()(ast::nondigit const &a);
		FilterFactory &operator()(ast::anyword const &a);
		FilterFactory &operator()(ast::nonword const &a);
		FilterFactory &operator()(ast::anywhitespace const &a);
};

} // end namespace visitors

#endif // PARSER__VISITORS__FILTER_FACTORY_VISITOR