#include "regex.hpp"

#include "automata/nfa/lva.hpp"
#include "automata/nfa/sva.hpp"
#include "automata/nfa/udfa.hpp"
#include "evaluation/evaluation.hpp"
#include "parse/parser.hpp"

namespace rematch {

RegEx::RegEx(std::string_view pattern, rematch::RegExOptions rgx_opts)
    : pattern_(pattern),
      VA_(regex2LVA(pattern)),
      flags_(parseFlags(rgx_opts)),
      variables(VA_->varFactory()->variables()) {

  vfactory_ = VA_->varFactory();
  eVA_ = std::make_shared<ExtendedVA>(*VA_, Anchor::kUnanchored);

  // std::cout << "LogicalVA:\n" << *VA_ << "\n\n";
}

// Explicitly declared here for correct use of unique_ptr later
RegEx::~RegEx() {}

// MatchIterator RegEx::findIter(std::shared_ptr<Document> d, Anchor a) {
//   Evaluator* eval;
//   std::shared_ptr<StrDocument> strd =
//   std::static_pointer_cast<StrDocument>(d); eval = new
//   SegmentEvaluator(*this, strd, a); return MatchIterator(eval); if (flags_ &
//   kEarlyOutput) {
//     if (flags_ & kLineByLine) {
//       eval = new EarlyOutputLineEvaluator(*this, d);
//     } else {
//       // if(dman_->nfa().is_dfa_searchable()) {
//         std::shared_ptr<StrDocument> strd =
//         std::static_pointer_cast<StrDocument>(d); eval = new
//         EarlyOutputFilterEvaluator(*this, strd);
//       // } else {
//       //   eval = new EarlyOutputEvaluator(*this, d);
//       // }
//     }
//   } else {
//     if (flags_ & kLineByLine) {
//       eval = new LineEvaluator(*this, d);
//     } else {
//       eval = new NormalEvaluatorNew(*this, d);
//     }
//   }
//   return MatchIterator(eval);
// }

MatchIterator RegEx::find_iter(std::string_view d, Anchor a) {
  Evaluator* eval;
  auto* stats = new EvalStats();
  if (flags_ & kSearching) {
    eval = new SegmentEvaluator(*this, d, a, *stats);
  } else if (flags_ & kUnambiguous && !eVA_->is_ambiguous()) {
    eval = new NormalEvaluator<UDFA>(*this, d, a, *stats);
  } else {
    eval = new NormalEvaluator<DFA>(*this, d, a, *stats);
  }
  return {eval, stats};
}

// Match_ptr RegEx::find(const std::string &text) {
// auto document = std::make_shared<StrDocument>(text);
// return EarlyOutputEvaluator(*this, document).next();
// }

RegEx::flags_t RegEx::parseFlags(rematch::RegExOptions rgx_opts) {
  flags_t ret =
      rgx_opts.multi_line() * kMultiLine |
      rgx_opts.line_by_line() * kLineByLine | rgx_opts.dot_nl() * kDotNL |
      rgx_opts.early_output() * kEarlyOutput |
      rgx_opts.save_anchors() * kSaveAnchors |
      rgx_opts.searching() * kSearching | rgx_opts.macrodfa() * kMacroDFA |
      rgx_opts.unambiguous() * kUnambiguous;
  return ret;
}

}  // end namespace rematch
