#include "parser.hpp"

namespace rematch {

LogicalVA doParse(const std::string &input) {
  std::cout << "Input: " << input << std::endl;

  // * Parse Tree
  antlr4::ANTLRInputStream stream(input);
  REmatchLexer lexer(&stream);
  antlr4::CommonTokenStream tokens(&lexer);
  REmatchParser parser(&tokens);
  REmatchParser::RootContext *root = parser.root();

  // * Variable Factory
  visitors::VariableFactoryVisitor vfv;
  VariableFactory vfact = vfv.get_vfact(root);
  std::shared_ptr<VariableFactory> vfact_ptr = std::make_shared<VariableFactory>(vfact);

  // * Filter Factory
  visitors::FilterFactoryVisitor ffv;
  FilterFactory ffact = ffv.get_ffact(root);
  std::shared_ptr<FilterFactory> ffact_ptr = std::make_shared<FilterFactory>(ffact);

  // * Logical VA
  visitors::AutomataVisitor av(vfact_ptr, ffact_ptr);
  LogicalVA lva = av.get_lva(root);
  lva.set_factories(vfact_ptr, ffact_ptr);

  return lva;
}

std::unique_ptr<LogicalVA> regex2LVA(std::string regex) {
  LogicalVA lva = doParse(regex);
  std::unique_ptr<LogicalVA> lva_ptr = std::make_unique<LogicalVA>(lva);
  return lva_ptr;
}

} // end namespace rematch