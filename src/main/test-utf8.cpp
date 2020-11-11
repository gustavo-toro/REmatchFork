#include <iterator>
#include <vector>
#include <string>

#include <utf8.h>

#include "regex/regex.hpp"
#include "document.hpp"
#include "eval.hpp"
#include "util.hpp"

int main(int argc, char *argv[]) {

  using utf32_str = std::vector<uint>;

  std::vector<std::string> texts = {
    "Ils préfèrent les mêmes chaussures que ma sœur",
    "Ils preferent les memes chaussures que ma sour"
  };

  utf32_str u32_text;

  utf8::utf8to32(texts[0].begin(), texts[0].end(), std::back_inserter(u32_text));

  std::cout << "U32 size: " << u32_text.size() << "\n";

  for(auto &c: u32_text) {
    std::cout << c << " ";
  }

  std::cout << '\n';

  for(auto &text: texts) {
    std::cout << "The text: \"" << text << "\"\n";
    std::cout << "The size: " << text.size() << "\n";
  }
}