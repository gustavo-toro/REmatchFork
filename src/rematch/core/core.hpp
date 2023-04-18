#ifndef CORE__CORE_HPP
#define CORE__CORE_HPP

#include "filtering_module/search_variable_set_automaton.hpp"
#include "filtering_module/segment_identificator.hpp"

std::string_view document;
SearchDFA& search_dfa;
size_t curr_idx = 0;
Enumerator enumerator;
auto final_node;
auto segment_identificator = SegmentIdentificator(search_dfa, document);

Match* next_core(size_t bof_idx, size_t eof_idx) {
Enumeration:
  if (enumerator.has_next())
    return enumerator.next();

Evaluation:
  if (curr_idx < eof_idx) {
    if (curr_idx < bof_idx)
      init_evaluation_phase();  // TODO:

    if (evaluation_phase())  // TODO:
      pass_outputs();        // TODO:
    enumerator.add_node(final_node);
    goto Enumeration;
  }

  return nullptr;
}

void main() {
  // Init() (this would becalled once)
  if (!segment_identificator.has_next())
    return;
  Span output_span = segment_identificator.next();

// Next() (this would be called multiple times)
Core:
  auto m = next_core(output_span.first, output_span.second, document);
  if (m != nullptr)
    std::cout << "Match: " << m << std::endl;

Segment:
  if (segment_identificator.has_next()) {
    Span output_span = segment_identificator.next();
    goto Core;
  }

  // TODO: Set stats...
  return nullptr;
}

#endif