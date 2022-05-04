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

  Match(std::shared_ptr<VariableFactory> vf, std::shared_ptr<MatchData> md)
      : var_factory_(vf), data(md) {
    it_lower = data->begin();
    it_upper = data->end();
  }

  Match(std::shared_ptr<VariableFactory> vf, std::shared_ptr<MatchData> md, MatchData::const_iterator s, MatchData::const_iterator e)
      : var_factory_(vf), data(md), it_lower(s), it_upper(e) { }

  // Returns a variable's iterator of spans
  SpanIterator spans(std::string var) const;
  // Returns a variable's span
  Span* span(std::string var) const;
  // Return a variable's iterator of captured substrings
  StringIterator groups(std::string var, std::shared_ptr<StrDocument>& doc) const;
  // Returns a variable's captured substring
  std::string* group(std::string var, std::shared_ptr<StrDocument>& doc) const;
  // Returns a pointer to a Match with spans between s
  Match_ptr submatch(Span* s) const;
  // Returns a vector with the variable names in order
  std::vector<std::string> variables() const;
  // Pretty print
  std::string pprint(std::shared_ptr<StrDocument>& doc) const;
  // ostream representation
  friend std::ostream& operator<<(std::ostream& os, Match& m);

 private:
  // Access to variable names
  std::shared_ptr<VariableFactory> var_factory_;
  // Stores opening and closing variables ordered by position
  std::shared_ptr<MatchData> data;
  // Range of this match. Submatches should be a subrange of its "parent"
  MatchData::const_iterator it_lower;
  MatchData::const_iterator it_upper;

};  // end class Match

}  // end namespace rematch

#endif  // MATCH_HPP