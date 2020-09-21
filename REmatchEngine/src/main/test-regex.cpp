#include "regex/regex.hpp"
#include "document.hpp"
#include "eval.hpp"
#include "util.hpp"

int main(int argc, char *argv[]) {
  rematch::RegEx rgx(".*!x{d}.*");
  const std::string doc = "dog";

  rematch::Match_ptr match, match2;

  int count = 0;

  match = rgx.find(doc);

  std::cout << *match << '\n';

  match2 = rgx.find(doc);

  std::cout << *match2 << '\n';

  // while(match = rgx.findIter(doc)) {
  //   std::cout << *match << '\n';
  //   count++;
  // }

  // std::cout << "Count: " << count << '\n';
}