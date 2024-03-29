#include <iostream>

#include <re2/re2.h>

#include "util/util.hpp"

int main(int argc, char const *argv[]) {

  if (argc != 3) {
    std::cerr << "Error parsing args.\nUsage:\n\t" << argv[0]
              << " [rgx_file] [doc_file]\n";
    exit(1);
  }

  std::string doc, rgx;

  rgx = rematch::util::file2str(argv[2]);
  doc = rematch::util::file2str(argv[1]);

  re2::StringPiece input(doc);

  RE2::Options opts;
  opts.set_log_errors(false);

  RE2 pattern(rgx, opts);

  std::ofstream logfile("logs/re2_force_all.log");

  re2::StringPiece supermatch, match;
  int count = 0;

  while (RE2::PartialMatch(input, pattern, &supermatch)) {
    count++;
    logfile << "x = |" << supermatch.data() - doc.data() << ","
                     << supermatch.data() - doc.data() + supermatch.size()
                     << ">\n";
    supermatch.remove_suffix(1);
    while (RE2::PartialMatch(supermatch, pattern, &match)) {
      count++;
      logfile << "x = |" << match.data() - doc.data() << ","
                     << match.data() - doc.data() + match.size()
                     << ">\n";

      supermatch.remove_suffix(supermatch.size() - match.size() + 1);
    }
    // Jump to the start of the next match
    input.remove_prefix(supermatch.data() - input.data() + 1);
  }

  // std::cout << "Match: \"" << match << "\"\n";

  std::cout << count << '\n';

  logfile.close();

  return 0;
}