#include <iostream>

#include "regex/regex_options.hpp"
#include "regex/regex.hpp"
#include "document.hpp"
#include "eval.hpp"
#include "util.hpp"

int main(int argc, char *argv[]) {
  // rematch::RegExOptions rgx_opts;
  // rgx_opts.set_start_anchor(false);
  // rgx_opts.set_end_anchor(false);

  rematch::RegEx rgx("!x{a+}");
  const std::string doc = "aaaaaa";

  int count = 0;

  auto eval_iter = rgx.findIter(doc, kUnanchored);

  while(eval_iter.hasNext()) {
    auto match = eval_iter.next();
    std::cout << match << '\n';
    count++;
  }

  std::cout << "Count: " << count << '\n';
  count = 0;

  const std::string doc2 = "aabbbbaaa";

  auto eval_iter2 = rgx.findIter(doc2, kSingleAnchor);

  while(eval_iter2.hasNext()) {
    auto match = eval_iter2.next();
    std::cout << match << '\n';
    count++;
  }

  std::cout << "Count: " << count << '\n';
}