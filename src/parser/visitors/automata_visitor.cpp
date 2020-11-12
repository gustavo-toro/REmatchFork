#include "automata_visitor.hpp"

#include "parser/ast.hpp"
#include "automata/lva.hpp"
#include "automata/lvastate.hpp"
#include "factories/factories.hpp"
#include "charclass.hpp"

namespace visitors {

regex2LVA::regex2LVA(std::unique_ptr<VariableFactory>& v,
										 std::unique_ptr<FilterFactory>& f)
	: vFact(std::move(v)), fFact(std::move(f)) {}

lva_ptr regex2LVA::operator()(ast::altern const &a) const {
	auto A = (*this)(a.front());
	if(a.size()>1) {
		for (size_t i = 1; i < a.size(); ++i) {
			A->alter(*(*this)(a[i]));
		}
	}
	return A;
}

lva_ptr regex2LVA::operator()(ast::concat const &c) const {
	auto A = (*this)(c.front());
	if(c.size()>1) {
		for (size_t i = 1; i < c.size(); ++i) {
			A->cat(*(*this)(c[i]));
		}
	}
	return A;
}

lva_ptr regex2LVA::operator()(ast::iter const &it) const {
	auto A = (*this)(it.expr);
	for (auto &rep: it.repetitions) {
		assert(rep.start_ >= 0);
		if(rep.start_ == 0 && rep.end_ == -1)
			A->kleene();
		else if(rep.start_ == 0 && rep.end_ == 1)
			A->optional();
		else if(rep.start_ == 1 && rep.end_ == -1)
			A->strict_kleene();
		else
			A->repeat(rep.start_, rep.end_);
	}

	return A;
}

lva_ptr regex2LVA::operator()(ast::group const &g) const {
	return boost::apply_visitor(*this, g);
}

lva_ptr regex2LVA::operator()(ast::parenthesis const &p) const {
	return (*this)(p.root);
}

lva_ptr regex2LVA::operator()(ast::assignation const &a) const {
	auto A = (*this)(a.root);
	A->assign(a.var);
	return A;
}

lva_ptr regex2LVA::operator()(ast::atom const &a) const {
	return boost::apply_visitor(*this, a);
}

lva_ptr regex2LVA::operator()(ast::charset const &cs) const {
	auto A = std::make_unique<LogicalVA>(vFact, fFact);
	LVAState* fState = new LVAState();
	fState->setFinal(true);
	A->states.push_back(fState);
	A->finalStates.push_back(fState);

	CharClass chs = CharClass(cs);

	A->initState()->addFilter(fFact->getCode(chs), fState);

	return A;
}

lva_ptr regex2LVA::operator()(char const &a) const {
	return std::make_unique<LogicalVA>(a, vFact, fFact);
}

lva_ptr regex2LVA::operator()(ast::anychar const &a) const {
	return std::make_unique<LogicalVA>(ANYCHAR, false, vFact, fFact);
}

lva_ptr regex2LVA::operator()(ast::anydigit const &a) const {
	return std::make_unique<LogicalVA>(ANYDIGIT, false, vFact, fFact);
}

lva_ptr regex2LVA::operator()(ast::nondigit const &a) const {
	return std::make_unique<LogicalVA>(ANYDIGIT, true, vFact, fFact);
}

lva_ptr regex2LVA::operator()(ast::anyword const &a) const {
	return std::make_unique<LogicalVA>(ANYWORD, false, vFact, fFact);
}

lva_ptr regex2LVA::operator()(ast::nonword const &a) const {
	return std::make_unique<LogicalVA>(ANYWORD, true, vFact, fFact);
}

lva_ptr regex2LVA::operator()(ast::anywhitespace const &a) const {
	return std::make_unique<LogicalVA>(ANYSPACE, false, vFact, fFact);
}

lva_ptr regex2LVA::operator()(ast::nonwhitespace const &a) const {
	return std::make_unique<LogicalVA>(ANYSPACE, true, vFact, fFact);
}

lva_ptr regex2LVA::operator()(ast::anchor const &a) const {
	if(a.is_start)
		return std::make_unique<LogicalVA>(kStartAnchor, false, vFact, fFact);
	else
		return std::make_unique<LogicalVA>(kEndAnchor, false, vFact, fFact);
}


} // end namespace visitors