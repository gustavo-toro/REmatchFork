#ifndef RANKED_EVALUATOR_HPP
#define RANKED_EVALUATOR_HPP

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <sstream>

#include "evaluation/evaluator.hpp"
#include "match.hpp"
#include "evaluation/document/document.hpp"

#include "automata/wnfa/wnfa.hpp"

#include "structs/capture_place.hpp"

namespace rematch {
namespace ranked {

// using WeightedVA = WeightedVA<CapturePlace, double>;

class RankedEvaluator : public Evaluator {

 public:
  RankedEvaluator(WeightedVA<>& wva, const std::string &d);

  virtual Match_ptr next();

 private:

  // Initialize the automaton and enumeration
  void init();

  void preprocessing();

  void read(char a, long pos);

  Match_ptr enumerate();

  WeightedVA<>& automaton_;

  const std::string &text_;

  std::vector<WeightedVA<>::State*> current_states_;
  std::vector<WeightedVA<>::State*> new_states_;

  long i_pos_ = 0;

  // HeapOfWords<CapturePlace, double>* h_out_ = new HoWPaper<CapturePlace,double>();
  HoWPaper<CapturePlace, double>* h_out_ = new HoWPaper<CapturePlace,double>();

  bool finished_preprocessing_ = false;

  // Enumerator enumerator_;
}; // end class Evaluator

} // namespace ranked

} // namespace rematch

#endif // RANKED_EVALUATOR_HPP