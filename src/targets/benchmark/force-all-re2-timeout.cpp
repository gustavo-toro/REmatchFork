#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include <re2/re2.h>

#include "util/timer.hpp"
#include "util/util.hpp"

using namespace std::chrono_literals;

int f(re2::StringPiece &input, RE2 &pattern, int &count) {
  re2::StringPiece supermatch, match;
  size_t inp_sz = input.size(); // Original size

  for (size_t i = 0; i < inp_sz; i++) {
    if (RE2::PartialMatch(input, pattern, &supermatch)) {
      size_t spmatch_size = supermatch.size();
      for (size_t j = 0; j < spmatch_size; j++) {
        if (RE2::PartialMatch(supermatch, pattern, &match)) {
          count++;
          // std::cout << "|" << match.data() - doc.data() << ","
          //                  << match.data() - doc.data() + match.size() <<
          //                  ">\n";
        } else
          break;
        // No se puede asegurar que no haya output en el resto de los
        // prefijos.
        supermatch.remove_suffix(supermatch.size() - match.size() + 1);
      }
      // std::cout << "Match: \"" << match << "\"\n";

      // Jump to the start of the next match
      input.remove_prefix(supermatch.data() - input.data() + 1);
    } else {
      input.remove_prefix(input.size());
    };
  }
  return 1;
}

int f_wrapper(re2::StringPiece &input, RE2 &pattern, int &count) {
  std::mutex m;
  std::condition_variable cv;
  int retValue;

  std::thread t([&cv, &retValue, &input, &pattern, &count]() {
    retValue = f(input, pattern, count);
    cv.notify_one();
  });

  t.detach();

  {
    std::unique_lock<std::mutex> l(m);
    if (cv.wait_for(l, 60s) == std::cv_status::timeout)
      throw std::runtime_error("Timeout");
  }

  return retValue;
}

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
  re2::StringPiece original(doc);

  RE2 pattern(rgx);

  Timer timer;

  int count = 0;

  try {
    f_wrapper(input, pattern, count);
  } catch (std::runtime_error &e) {
    // std::cout << e.what() << std::endl;
  }

  double t = timer.elapsed() / 1000;

  std::cout << "time: " << t << "s\n";

  int consumed = input.data() - original.data();

  std::cout << "consumed chars: " << consumed << "\n";

  double consumed_size = consumed;

  std::cout << "consumed: " << consumed_size << " Kb\n";

  double throughput = consumed_size / t;

  std::cout << throughput << " B/s\n";

  std::cout << "count: " << count << "\n";

  return 0;
}