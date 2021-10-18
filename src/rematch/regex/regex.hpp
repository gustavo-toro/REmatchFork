#ifndef SRC_REMATCH_REGEX_REGEX_HPP
#define SRC_REMATCH_REGEX_REGEX_HPP

#include <string>
#include <memory>

#include "match.hpp"
#include "memmanager.hpp"
#include "enumeration.hpp"

#include "det/detmanager.hpp"
#include "automata/nfa/eva.hpp"
#include "automata/dfa/dfa.hpp"
#include "regex/regex_options.hpp"
#include "automata/nfa/lva.hpp"
#include "matchiterator.hpp"
#include "evaluation/document/document.hpp"
#include "automata/wnfa/wnfa.hpp"

namespace rematch {

class Evaluator;

class RegEx {

 public:

  using flags_t = uint8_t;

  RegEx(std::string regex, RegExOptions opt = RegExOptions());
  RegEx(LogicalVA* A, RegExOptions opt = RegExOptions());
  RegEx(ranked::WeightedVA<>* wVA, RegExOptions opt = RegExOptions());

  ~RegEx();

  // std::string uniformGenerate(uint32_t n);
  std::string getRegex();

  enum RegExFlags {
    kNoFlags     = 0,
    kMultiLine   = 1<<0,
    kDotNL       = 1<<1,
    kLineByLine  = 1<<2,
    kEarlyOutput = 1<<3,
    kSaveAnchors = 1<<4,
    kRanked      = 1<<5, // Ranked enumeration
    kDoCrossProduct = 1<<6
  };

  enum Anchor {
    UNANCHORED,
    ANCHOR_START,
    ANCHOR_BOTH
  };

  // Calls the evaluator to get first
  Match_ptr find(const std::string &text);

  MatchIterator findIter(std::shared_ptr<Document> d);

  int varCount() const {return dman_->varFactory()->size();}

  // Getters

  const std::string pattern() const {return pattern_;}

  // Detmanager stuff.

  DetManager& detManager() {return *dman_;};
  DetManager& rawDetManager() {return *raw_dman_;};


  size_t capture_counter() const;
  size_t reading_counter() const;
  size_t direct_counter() const;
  size_t single_counter() const;
  size_t direct_single_counter() const;
  size_t direct_multi_counter() const;
  size_t multi_counter() const;
  size_t empty_counter() const;
  size_t det_counter() const;
  size_t miss_counter();

  size_t dfa_counter();
  size_t nfa_counter();
  size_t mdfa_counter();

  private:

  static flags_t parseFlags(RegExOptions rgx_opt);

  const std::string pattern_;

  // DetManager for capture automaton.
  std::unique_ptr<DetManager> dman_;

  // DetManager for raw automaton.
  std::unique_ptr<DetManager> raw_dman_;

  // Regex flags.
  flags_t flags_;

  // Is DFA fully computed.
  bool full_dfa_;

  ranked::WeightedVA<>* wva_;

}; // end class Regex

} // end namespace rematch

#endif // SRC_REMATCH_REGEX_REGEX_HPP
