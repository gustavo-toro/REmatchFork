#ifndef EVALUATION__SEGMENT_EVALUATOR_HPP
#define EVALUATION__SEGMENT_EVALUATOR_HPP

#include <string_view>

#include "filtering_module/segment_identificator.hpp"
#include "library_interface/regex.hpp"

namespace rematch {
namespace evaluation {

class SegmentEvaluator {
 public:
  SegmentEvaluator(Regex& regex, std::string_view document);

  void next();

 private:
  Regex& regex;
  std::string_view document;

  SegmentIdentificator segment_identificator;

  size_t current_index = 0;
  Span current_segment;

  void init_evaluation_phase(size_t index);

  bool evaluation_phase();

  void pass_outputs();
};
}  // namespace evaluation
}  // namespace rematch

#endif