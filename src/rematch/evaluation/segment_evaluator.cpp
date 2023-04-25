#include "segment_evaluator.hpp"

namespace rematch {
namespace evaluation {

SegmentEvaluator::SegmentEvaluator(Regex& regex, std::string_view document)
    : regex(regex), document(document) {
  // TODO: Get search_dfa from somewhere
  segment_identificator = SegmentIdentificator(search_dfa, document);
  init_evaluation_phase(0);
}

void SegmentEvaluator::next() {
Enumeration:
  if (enumerator.has_next())
    return enumerator.next();

Evaluation:
  if (current_index < current_segment.second) {
    if (current_index < current_segment.first)
      init_evaluation_phase(current_segment.first);

    if (evaluation_phase())
      pass_outputs();
    enumerator.add_node(final_node);
    goto Enumeration;
  }

  if (segment_identificator.has_next()) {
    current_segment = segment_identificator.next();
    goto Evaluation;
  }

  return nullptr;
}

void SegmentEvaluator::init_evaluation_phase(int64_t pos) {
  // TODO: Implement this
}

void SegmentEvaluator::evaluation_phase() {
  // TODO: Implement this
  return false;
}

void SegmentEvaluator::pass_outputs() {
  // TODO: Implement this
}

}  // namespace evaluation
}  // namespace rematch
