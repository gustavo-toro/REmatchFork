#ifndef PARSER__VISITORS__AUTOMATA_VISITOR
#define PARSER__VISITORS__AUTOMATA_VISITOR

#include <memory>

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#include "automata/lva.hpp"
#include "parser/ast.hpp"

namespace visitors {

struct regex2LVA : boost::static_visitor<LogicalVA&> {
	private:
		std::shared_ptr<VariableFactory> vFact;
		FilterFactory& fFact;
	public:

		regex2LVA(std::unique_ptr<VariableFactory> &v, FilterFactory& f);

		LogicalVA &operator()(ast::altern const &a) const;
		LogicalVA &operator()(ast::concat const &c) const;
		LogicalVA &operator()(ast::iter const &it) const;
		LogicalVA &operator()(ast::group const &g) const;
		LogicalVA &operator()(ast::parenthesis const &p) const;
		LogicalVA &operator()(ast::assignation const &a) const;
		LogicalVA &operator()(ast::atom const &a) const;
		LogicalVA &operator()(ast::charset const &cs) const;
		LogicalVA &operator()(char const &a) const;
		LogicalVA &operator()(ast::anychar const &a) const;
		LogicalVA &operator()(ast::anydigit const &a) const;
		LogicalVA &operator()(ast::nondigit const &a) const;
		LogicalVA &operator()(ast::anyword const &a) const;
		LogicalVA &operator()(ast::nonword const &a) const;
		LogicalVA &operator()(ast::anywhitespace const &a) const;
};

} // namespace visitors

#endif // PARSER__VISITORS__AUTOMATA_VISITOR