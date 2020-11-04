#ifndef EVAL_HPP
#define EVAL_HPP

#include <string>
#include <vector>
#include <memory>

#include "regex/regex.hpp"
#include "match.hpp"
#include "enumeration.hpp"
#include "automata/detautomaton.hpp"
#include "memmanager.hpp"
#include "document.hpp"

class DetState;

namespace rematch {

class Evaluator {
 public:
  friend class RegEx;

  enum EvalOptions {
    kLineByLine    = 1<<2,
    kEarlyOutput   = 1<<3,
    kAllFlags      = kEarlyOutput | kLineByLine
  };

  Match next();
  bool hasNext();

  Evaluator(RegEx& rgx, std::istream& input, uint8_t eval_options=0);
  Evaluator(RegEx& rgx, const std::string& input, uint8_t eval_options=0);

 private:

  void init();

  bool hasNextTT();
  bool hasNextTF();
  bool hasNextFT();
  bool hasNextFF();

  void captureT(size_t i);
  void captureF(size_t i);

  void readingT(char a, size_t i);
  void readingF(char a, size_t i);

  inline bool inlinedHasNext(bool early_output, bool line_by_line);

  inline void capture(size_t i, bool early_output);
  inline void reading(char a, size_t i, bool early_output);

  void initAutomaton(size_t i);

  bool match();

  DetAutomaton& rawDFA();
  DetAutomaton& DFA();

  std::shared_ptr<RegEx> rgx_;
  std::unique_ptr<Enumerator> enumerator_;
  MemManager memory_manager_;

  std::unique_ptr<Document> text_;
  std::string line_;

  std::vector<DetState*> current_states_;
  std::vector<DetState*> new_states_;
  std::vector<DetState*> capture_states_;

  NodeList output_nodelist_;

  bool early_output_;
  bool line_by_line_;

  bool document_ended_;
  bool direct_text_;

  size_t i_pos_;
  size_t i_start_;
  size_t nlines_;

  size_t capture_counter_;
  size_t reading_counter_;
}; // end class Evaluator

} // namespace rematch

#endif // EVAL_HPP