#include "regex.hpp"
#include "parser/parser.hpp"
#include "eval.hpp"

namespace rematch {

RegEx::RegEx(std::string pattern, rematch::RegExOptions rgx_opts)
    : pattern_(pattern),
      dman_(pattern, rgx_opts.anchors()),
      raw_dman_(pattern, rgx_opts.anchors(), 1),
      flags_(parseFlags(rgx_opts)),
      anchors_(rgx_opts.anchors()) {}

// Explicitly declared here for correct use of unique_ptr later
RegEx::~RegEx() {}

std::string RegEx::uniformGenerate(uint32_t n) {
  if(!full_dfa_) {
    dman_.computeFullDetAutomaton();
    full_dfa_ = true;
  }
  return dman_.uniformSample(n);
}


EvaluatorIter RegEx::findIter(const std::string &text) {
  auto eval = new Evaluator(*this, text, Evaluator::kAllFlags & flags_);
  return EvaluatorIter(eval);
}

EvaluatorIter RegEx::findIterFile(std::istream &is) {
  auto eval = new Evaluator(*this, is, Evaluator::kAllFlags & flags_);
  return EvaluatorIter(eval);
}

Match_ptr RegEx::find(const std::string &text) {
  auto eval = Evaluator(*this, text, flags_ & Evaluator::kEarlyOutput);

  return eval.next();
}


uint8_t RegEx::parseFlags(rematch::RegExOptions rgx_opts) {
  uint8_t ret =  rgx_opts.multi_line()    * kMultiLine    |
                 rgx_opts.line_by_line()  * kLineByLine   |
                 rgx_opts.dot_nl()        * kDotNL        |
                 rgx_opts.early_output()  * kEarlyOutput  |
                 rgx_opts.save_anchors()  * kSaveAnchors;
  return ret;
}

} // end namespace rematch




