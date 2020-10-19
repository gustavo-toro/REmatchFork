#ifndef LVA_HPP
#define LVA_HPP

#include <string>
#include <vector>
#include <memory>

#include "anchors.hpp"

class VariableFactory;
class FilterFactory;
class LVAState;

class LogicalVA {
  using vf_uptr = std::unique_ptr<VariableFactory>;
  using vf_sptr = std::shared_ptr<VariableFactory>;

  using ff_sptr = std::shared_ptr<FilterFactory>;
  /* A basic implementation of a Variable Automaton  */
 public:
  std::vector<LVAState*> states;
  std::vector<LVAState*> finalStates;

  // Empty LogicalVA construction (only one LVAState)
  LogicalVA();

  LogicalVA(vf_sptr vFact, ff_sptr fFact);

  // LogicalVA(std::string pattern, bool raw=false);

  // Atomic LogicalVA construction
  LogicalVA(const char &a);
  LogicalVA(const char &a, vf_sptr vf, ff_sptr fFact);
  LogicalVA(int spec, bool negated, vf_sptr vf, ff_sptr fFact);

  LogicalVA(const LogicalVA &A);

  // Copy constructor
  // LogicalVA(const LogicalVA &A);

  // Computes epsilon transitions between capture states.
  void adapt_capture_jumping();

  // Adds transitions according to an anchor
  void adapt_anchors(Anchor &anchor);

  // LogicalVA operations, all modify the current LogicalVA to get the result
  // (the operations are inplace)

  void cat(LogicalVA &a2);                 // Equivalent to R1.R2 in VarRegEx
  void alter(LogicalVA &a2);               // Equivalent to R1|R2 in VarRegEx
  void kleene();                           // Equivalent to R* in VarRegEx
  void strict_kleene();                    // Equivalent to R+ in VarRegEx
  void optional();                         // Equivalent to R? in VarRegEx
  void assign(std::string varName);  // Equivalent to !x{R} in VarRegEx
  void repeat(int min, int max);

  std::string pprint();

  std::shared_ptr<VariableFactory> varFactory() {return v_factory_;}
  std::shared_ptr<FilterFactory> filterFactory() {return f_factory_;}

  LVAState* initState() const {return init_state_;}

 private:

  LVAState* init_state_;

  vf_sptr v_factory_;
  ff_sptr f_factory_;
};

#endif