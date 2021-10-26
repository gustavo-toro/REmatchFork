#include "charclass_visitor.hpp"

#include "charclass.hpp"

namespace rematch {
namespace visitors {

CharClassBuilder charclass_visitor::operator()(ast::atom const &a) const {
  return boost::apply_visitor(*this, a);
}

CharClassBuilder charclass_visitor::operator()(ast::charset const &cs) const {
  return CharClassBuilder(cs);
}

CharClassBuilder charclass_visitor::operator()(ast::special const &s) const {
  return CharClassBuilder(s);
}

CharClassBuilder charclass_visitor::operator()(char const &a) const {
  return CharClassBuilder(a);
}

} // end namespace visitors
} // end namespace rematch