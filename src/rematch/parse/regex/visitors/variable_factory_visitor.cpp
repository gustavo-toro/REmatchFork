#include "variable_factory_visitor.hpp"

#include <iostream>
#include <typeinfo>

#include "parse/regex/exceptions.hpp"
#include "parse/regex/ast.hpp"

namespace rematch {
namespace visitors {

vfptr regex2vars::operator()(ast::altern const &node) const {
  // Call the same struct on the first member of altern
	auto vfact = (*this)(node.front());

  // If there are more members on the altern, check that the same variables
  // are used (so that the regex is functional).
	if(node.size() > 1) {
		for (size_t i = 1; i < node.size(); ++i)
			if(!(*vfact == *((*this)(node[i])))) {
				throw parsing::BadRegex("Not a functional regex.");
			};
	}
	return vfact;
}

vfptr regex2vars::operator()(ast::concat const &c) const {
	// std::cout << "c.size() = " << c.size() << "\n";
	
	auto vfact = (*this)(c.front());
	
	// Checking for opened or paired single variables
	vfact->checkLeftHandSide();

	if(c.size() > 1) {
		for (size_t i = 1; i < c.size(); ++i) {
      auto current = (*this)(c[i]);
			vfact->merge(*current); // Checking for functional regex inside merge
		}
	}
	// verificar todos pareados
	//vfact -> checkAfterMerge();


	return vfact;
}

vfptr regex2vars::operator()(ast::iter const &it) const {
	auto vfact = (*this)(it.expr);
	if(!it.repetitions.empty() && !vfact->empty()){
		throw parsing::BadRegex("Not a functional regex.");
	}
	return vfact;
}

vfptr regex2vars::operator()(ast::group const &g) const {
	return boost::apply_visitor(*this, g);
}

vfptr regex2vars::operator()(ast::parenthesis const &p) const {
	return (*this)(p.root);
}

vfptr regex2vars::operator()(ast::assignation const &a) const {
	auto vfact = (*this)(a.root);

	if(vfact->contains(a.var)) {
    throw parsing::BadRegex("Not a functional regex.");
  }; // Check for functional regex

	vfact->add(a.var);
	return vfact;
}

vfptr regex2vars::operator()(ast::single_assignation const &sa) const {
	auto vfact = std::make_unique<VariableFactory>();
	
	vfact->addSingle(sa.var, sa.isLeft);
	
	return vfact;
}

vfptr regex2vars::operator()(ast::charset const &cs) const {
	return std::make_unique<VariableFactory>();
}

vfptr regex2vars::operator()(ast::assertion const &a) const {
	return std::make_unique<VariableFactory>();
}

vfptr regex2vars::operator()(char const &ch) const {
	return std::make_unique<VariableFactory>();
}

vfptr regex2vars::operator()(ast::special const &sp) const {
	return std::make_unique<VariableFactory>();
}

vfptr regex2vars::operator()(ast::atom const &a) const {
	return boost::apply_visitor(*this, a);
}

} // end namespace visitors
} // end namespace rematch