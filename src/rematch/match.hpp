#ifndef MATCH_HPP
#define MATCH_HPP

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "factories/factories.hpp"
#include "structs/match/spaniterator.hpp"
#include "structs/match/stringiterator.hpp"

namespace rematch {

class Match;
class Enumerator;
class ECS;
class StrDocument;
// FIXME: Change this
class Interface;

using Match_ptr = std::unique_ptr<Match>;
using Span = std::pair<int64_t, int64_t>;
using MatchData = std::map<int64_t, std::bitset<32>>;

// Represents a match for easy access to the captured spans and substrings.
// It doesn't store the correspondings substrings, so it's assumed that the
// sublaying document is available.
class Match {
  friend class Enumerator;
  friend class ECS;
  friend class Interface;

 public:
  Match() = default;

  Match(std::shared_ptr<VariableFactory> vf, std::vector<std::deque<int64_t>> m, MatchData d)
      : var_factory_(vf), data_(m), ordered_data(d) {}

  // Returns a variable's iterator of spans
  SpanIterator spans(std::string var) const;
  // Returns a variable's span
  Span* span(std::string var) const;
  // Return a variable's iterator of captured substrings
  StringIterator groups(std::string var, std::shared_ptr<StrDocument>& doc) const;
  // Returns a variable's captured substring
  std::string* group(std::string var, std::shared_ptr<StrDocument>& doc) const;
  // TODO: Implement this
  Match submatch(Span* s) const;
  // Returns a vector with the variable names in order
  std::vector<std::string> variables() const;
  // Pretty print
  std::string pprint(std::shared_ptr<StrDocument>& doc) const;
  // ostream representation
  friend std::ostream& operator<<(std::ostream& os, Match& m);

 private:
  // Access to variable names
  std::shared_ptr<VariableFactory> var_factory_;
  // Stores each variable spans
  std::vector<std::deque<int64_t>> data_;
  // Stores opening and closing variables ordered by position
  MatchData ordered_data;

};  // end class Match

}  // end namespace rematch

#endif  // MATCH_HPP