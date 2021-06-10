#include "parse/regex/parser.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  std::string rgx;
 	
  rgx = "!x{aa}x!";

  bool response = rematch::checkRegex(rgx);

  std::cout << rgx << response << '\n';

  return 0;
}