#ifndef EVALUATION__SEGMENT_EVALUATOR_HPP
#define EVALUATION__SEGMENT_EVALUATOR_HPP

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <sstream>

#include "parsing/logical_variable_set_automaton/logical_va.hpp"
#include "output_enumeration/mapping.hpp"

#include "filtering_module/search_variable_set_automaton/dfa/search_dfa.hpp"
#include "filtering_module/search_variable_set_automaton/dfa/search_dfa_state.hpp"

namespace rematch {
inline namespace filtering_module {

/**
  * The responsability of the SegmentIdentificator class is the same one
  * that the 'filering module' has on the paper:
  * REmatch: a regex engine for finding all matches
  * (Riveros, Van Sint Jan, Vrgoc 2023).
  *
  * The SegmentIdentificator identifies through has_next() and next()
  * the next segment of the document that has at least one output.
  */
class SegmentIdentificator {

 public:
  SegmentIdentificator(
      SearchDFA &search_dfa,
      std::string_view document
  );

  /**
   * next_is_computed_successfully() MUST be called before, if not, next() has undefined
   * behavior.
   */
  Span* next();

 private:
  /**
   * Tries to compute the next span that has an output
   * if it is computed correctly, next() will return that span
   * and the method will return true. If not, this method will
   * return false and next() will return nullptr.
   */
  bool next_is_computed_successfully();

  SearchDFA &search_dfa;
  std::string_view document;

  uint64_t i_src = 0;
  uint64_t i_min = 0;
  uint64_t i_max = 0;
};

}
}

#endif // EVALUATION__EOFILTER_EVALUATOR_HPP
