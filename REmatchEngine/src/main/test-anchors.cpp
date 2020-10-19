#include "regex/regex_options.hpp"
#include "regex/regex.hpp"
#include "document.hpp"
#include "eval.hpp"
#include "util.hpp"

int main(int argc, char *argv[]) {
  rematch::RegExOptions rgx_opts;
  rgx_opts.set_start_anchor(false);
  rgx_opts.set_end_anchor(false);

  rematch::RegEx rgx("!x{.<3,>}", rgx_opts);
  const std::string doc = "aabcad";

  rematch::Match_ptr match;

  int count = 0;

  while(match = rgx.findIter(doc)) {
    std::cout << *match << '\n';
    count++;
  }

  std::cout << "Count: " << count << '\n';
}