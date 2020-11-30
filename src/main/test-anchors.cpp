#include <iostream>

#include "regex/regex_options.hpp"
#include "regex/regex.hpp"
#include "document.hpp"
#include "eval.hpp"
#include "util.hpp"

int main(int argc, char *argv[]) {
  rematch::RegEx rgx("(^| )!x{\\S*[áéíóúカタカナ]\\S*}( |$)");
  std::vector<std::string> strs = {"123", "abc", "Línea カタカナ por línea hago match sólo donde hay tildes."};

  for(auto& s: strs) {
    // std::cout << "String: \"" << s << "\"\n";
    std::cout << "\tSize: " << s.size() << "\n";

    auto iter = rgx.findIter(s, kUnanchored);
    int count = 0;

    while(iter.hasNext()) {
      auto match = iter.next();
      std::cout << match << '\n';
      count++;
    }
    std::cout << "The count is: " << count << '\n';
  }




}