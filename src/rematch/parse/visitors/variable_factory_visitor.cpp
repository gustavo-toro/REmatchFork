#include "variable_factory_visitor.hpp"

#include <iostream>

#include "exceptions.hpp"
#include "parse/ast.hpp"

namespace rematch {
namespace visitors {

vfptr regex2vars::operator()(ast::altern const &node) const {
  // Call the same struct on the first member of altern
	auto vfact = (*this)(node.front());

	for (size_t i = 1; i < node.size(); ++i) {
		auto current = (*this)(node[i]);
		vfact->merge(*current);
	}
	return vfact;
}

vfptr regex2vars::operator()(ast::concat const &c) const {
	// std::cout << "c.size() = " << c.size() << "\n";
	auto vfact = (*this)(c.front());

	if(c.size() > 1) {
		for (size_t i = 1; i < c.size(); ++i) {
      auto current = (*this)(c[i]);
			vfact->merge(*current); // Checking for functional regex inside merge
		}
	}
	return vfact;
}

vfptr regex2vars::operator()(ast::iter const &it) const {
	return (*this)(it.expr);
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

vfptr regex2vars::operator()(ast::atom const &a) const {
	return std::make_unique<VariableFactory>();
}

} // end namespace visitors
} // end namespace rematch