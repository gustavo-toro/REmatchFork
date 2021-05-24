#ifndef EVALUATION__EOLINE_EVALUATOR_HPP
#define EVALUATION__EOLINE_EVALUATOR_HPP

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <sstream>

#include "evaluation/evaluator.hpp"
#include "regex/regex.hpp"
#include "match.hpp"
#include "enumeration.hpp"
#include "automata/dfa/dfa.hpp"
#include "memmanager.hpp"
#include "evaluation/document/document.hpp"
#include "automata/dfa/transition.hpp"

#include "automata/macrodfa/macrodfa.hpp"
#include "automata/macrodfa/macrostate.hpp"

namespace rematch {

class EarlyOutputLineEvaluator : public Evaluator {

 public:
  EarlyOutputLineEvaluator(RegEx& rgx, std::shared_ptr<Document> d);

  virtual Match_ptr next();

 private:

  inline void reading(char a, int64_t i);

  bool match(const std::string & s);

  inline void pass_current_outputs();
  inline void pass_outputs();

  DFA& dfa() {return rgx_.detManager().dfa();}
  DFA& rawDFA() {return rgx_.rawDetManager().dfa();}

  RegEx &rgx_;
  Enumerator enumerator_;
  MemManager memory_manager_;

  std::shared_ptr<Document> text_;

  MacroDFA macro_dfa_;

  MacroState* current_state_;

  LineIterator current_line_;
  std::string::const_iterator current_char_;

  static const size_t kSizeMaxOutputBuffer = 100;

  int64_t i_pos_;

  size_t out_buf_counter = 0;
}; // end class Evaluator

} // namespace rematch

#endif // EVALUATION__EOLINE_EVALUATOR_HPP