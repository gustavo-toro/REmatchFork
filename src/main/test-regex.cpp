#include "regex/regex.hpp"
#include "document.hpp"
#include "eval.hpp"
#include "util.hpp"

int main(int argc, char *argv[]) {
  rematch::RegEx rgx(".*!x{d}.*");
  const std::string doc = "dog";



  // int count = 0;

  // while(match = rgx.findIter(doc)) {
  //   std::cout << *match << '\n';
  //   count++;
  // }

  // std::cout << "Count: " << count << '\n';
}