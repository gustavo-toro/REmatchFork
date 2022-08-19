#include "parser.hpp"

namespace rematch {

void doParse(const std::string &input) {
  std::cout << "Input: " << input << std::endl;

  // * Parse Tree
  antlr4::ANTLRInputStream stream(input);
  REmatchLexer lexer(&stream);
  antlr4::CommonTokenStream tokens(&lexer);
  REmatchParser parser(&tokens);
  REmatchParser::RootContext *root = parser.root();
  std::cout << "Parse Tree Built." << std::endl;

  // * Variable Factory
  visitors::VariableFactoryVisitor vfv;
  VariableFactory vfact = vfv.get_vfact(root);
  std::cout << "Variable Factory Built." << std::endl;
  std::cout << vfact.pprint() << std::endl;

  // * Filter Factory
  visitors::FilterFactoryVisitor ffv;
  FilterFactory ffact = ffv.get_ffact(root);
  std::cout << "Filter Factory Built." << std::endl;
  std::cout << ffact.pprint() << std::endl;
}

std::unique_ptr<LogicalVA> regex2LVA(std::string regex) {
  doParse(regex);
  std::cout << "FINISHED!" << std::endl;

  return nullptr;
}

} // end namespace rematch