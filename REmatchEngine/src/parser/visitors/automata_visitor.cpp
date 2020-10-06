#include "automata_visitor.hpp"

#include "parser/ast.hpp"
#include "automata/lva.hpp"
#include "automata/lvastate.hpp"
#include "factories/factories.hpp"
#include "charclass.hpp"

namespace visitors {

regex2LVA::regex2LVA(std::unique_ptr<VariableFactory>& v, FilterFactory& f): vFact(std::move(v)), fFact(f) {}

LogicalVA& regex2LVA :: operator()(ast::altern const &a) const {
	LogicalVA& A = (*this)(a.front());
	if(a.size()>1) {
		for (size_t i = 1; i < a.size(); ++i) {
			A.alter((*this)(a[i]));
		}
	}
	return A;
}

LogicalVA& regex2LVA :: operator()(ast::concat const &c) const {
	LogicalVA& A = (*this)(c.front());
	if(c.size()>1) {
		for (size_t i = 1; i < c.size(); ++i) {
			A.cat((*this)(c[i]));
		}
	}
	return A;
}

LogicalVA& regex2LVA :: operator()(ast::iter const &it) const {
	LogicalVA& A = (*this)(it.expr);
	for (size_t i = 0; i < it.repetitions.size(); ++i) {
		switch(it.repetitions[i]) {
			case '?':
				A.optional(); break;
			case '*':
				A.kleene(); break;
			case '+':
				A.strict_kleene(); break;
		}
	}

	return A;
}

LogicalVA& regex2LVA :: operator()(ast::group const &g) const {
	return boost::apply_visitor(*this, g);
}

LogicalVA& regex2LVA :: operator()(ast::parenthesis const &p) const {
	return (*this)(p.root);
}

LogicalVA& regex2LVA :: operator()(ast::assignation const &a) const {
	LogicalVA& A = (*this)(a.root);
	A.assign(a.var);
	return A;
}

LogicalVA& regex2LVA :: operator()(ast::atom const &a) const {
	return boost::apply_visitor(*this, a);
}

LogicalVA& regex2LVA :: operator()(ast::charset const &cs) const {
	LogicalVA* A = new LogicalVA(vFact, fFact);
	LVAState* fState = new LVAState();
	fState->setFinal(true);
	A->states.push_back(fState);
	A->finalStates.push_back(fState);

	CharClass chs = CharClass(cs);

	A->initState()->addFilter(fFact.getCode(chs), fState);

	return *A;
}

LogicalVA& regex2LVA :: operator()(char const &a) const {
	LogicalVA* A = new LogicalVA(a, vFact, fFact);
	return *A;
}

LogicalVA& regex2LVA :: operator()(ast::anychar const &a) const {
	LogicalVA* A = new LogicalVA(ANYCHAR, false, vFact, fFact);
	return *A;
}

LogicalVA& regex2LVA :: operator()(ast::anydigit const &a) const {
	LogicalVA* A = new LogicalVA(ANYDIGIT, false, vFact, fFact);
	return *A;
}

LogicalVA& regex2LVA :: operator()(ast::nondigit const &a) const {
	LogicalVA* A = new LogicalVA(ANYDIGIT, true, vFact, fFact);
	return *A;
}

LogicalVA& regex2LVA :: operator()(ast::anyword const &a) const {
	LogicalVA* A = new LogicalVA(ANYWORD, false, vFact, fFact);
	return *A;
}

LogicalVA& regex2LVA :: operator()(ast::nonword const &a) const {
	LogicalVA* A = new LogicalVA(ANYWORD, true, vFact, fFact);
	return *A;
}

LogicalVA& regex2LVA :: operator()(ast::anywhitespace const &a) const {
	LogicalVA* A = new LogicalVA(ANYSPACE, false, vFact, fFact);
	return *A;
}


} // end namespace visitors