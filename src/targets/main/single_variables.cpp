#include "parse/regex/parser.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  int resp = rematch::checkRegex(argv[1]);
  std::cout << argv[1] << '\n';
  return 0;
}