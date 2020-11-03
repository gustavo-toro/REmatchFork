#ifndef PARSER__VISITORS__AUTOMATA_VISITOR
#define PARSER__VISITORS__AUTOMATA_VISITOR

#include <memory>

#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#include "automata/lva.hpp"
#include "parser/ast.hpp"

namespace visitors {

using lva_ptr = std::unique_ptr<LogicalVA>;

struct regex2LVA : boost::static_visitor<lva_ptr> {
	private:
		std::shared_ptr<VariableFactory> vFact;
		std::shared_ptr<FilterFactory> fFact;
	public:

		regex2LVA(std::unique_ptr<VariableFactory> &v, std::unique_ptr<FilterFactory> &f);

		lva_ptr operator()(ast::concat const &c) const;
		lva_ptr operator()(ast::iter const &it) const;
		lva_ptr operator()(ast::group const &g) const;
		lva_ptr operator()(ast::parenthesis const &p) const;
		lva_ptr operator()(ast::assignation const &a) const;
		lva_ptr operator()(ast::atom const &a) const;
		lva_ptr operator()(ast::altern const &a) const;
		lva_ptr operator()(ast::charset const &cs) const;
		lva_ptr operator()(char const &a) const;
		lva_ptr operator()(ast::anychar const &a) const;
		lva_ptr operator()(ast::anydigit const &a) const;
		lva_ptr operator()(ast::nondigit const &a) const;
		lva_ptr operator()(ast::anyword const &a) const;
		lva_ptr operator()(ast::nonword const &a) const;
		lva_ptr operator()(ast::anywhitespace const &a) const;
};

} // namespace visitors

#endif // PARSER__VISITORS__AUTOMATA_VISITOR