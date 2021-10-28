#ifndef SRC_REMATCH_PARSE_REGEX_VISITORS_FILTER_FACTORY_VISITOR_HPP
#define SRC_REMATCH_PARSE_REGEX_VISITORS_FILTER_FACTORY_VISITOR_HPP

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#include "factories/factories.hpp"
#include "parse/charclass/charclass_visitor.hpp"

namespace rematch {
namespace visitors {

using ff_ptr = std::unique_ptr<FilterFactory>;

struct regex2filters : boost::static_visitor<void> {
	private:
		ff_ptr filter_factory_;
		charclass_visitor charclass_visitor_;
	public:
		regex2filters();
		void operator()(ast::altern const &a);
		void operator()(ast::concat const &c);
		void operator()(ast::iter const &it);
		void operator()(ast::group const &g);
		void operator()(ast::parenthesis const &p);
		void operator()(ast::assignation const &a);
		void operator()(ast::atom const &a);
		void operator()(ast::charset const &cs);
		void operator()(char const &a);
		void operator()(ast::special const &a);

		ff_ptr get_factory();
};

} // end namespace visitors
} // end namespace rematch

#endif // SRC_REMATCH_PARSE_REGEX_VISITORS_FILTER_FACTORY_VISITOR_HPP
