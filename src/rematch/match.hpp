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

namespace rematch {

class Match;
class Enumerator;
class ECS;
class StrDocument;
// FIXME: Change this
class Interface;

#ifdef SWIG
using Match_ptr = Match*;
#else
using Match_ptr = std::unique_ptr<Match>;
#endif

using Span = std::pair<int64_t, int64_t>;

// Represents a match for easy access to the captured spans and substrings.
// It doesn't store the correspondings substrings, so it's assumed that the
// sublaying document is available.
class Match {
  friend class Enumerator;
  friend class ECS;
  friend class Interface;

 public:
  Match() = default;

  Match(std::shared_ptr<VariableFactory> vf, std::vector<std::deque<int64_t>> m, std::map<size_t, std::bitset<32>> om)
      : var_factory_(vf), data_(m), ordered_data_(om) {}

  // Returns a variable's [i, j) span
  Span span(std::string var) const;
  // TODO: Implement this
  // Iter<Span> spans(std::string var) const;
  // Returns a variable's captured substring
  std::string group(std::string var, std::shared_ptr<StrDocument>& doc) const;
  // TODO: Implement this
  // Iter<std::string> groups(std::string var, std::shared_ptr<StrDocument>& doc) const;
  // Returns a vector with the variable names in order
  std::vector<std::string> variables() const;
  // TODO: Implement this
  Match submatch(Span s) const;
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
  std::map<size_t, std::bitset<32>> ordered_data_;

};  // end class Match

}  // end namespace rematch

#endif  // MATCH_HPP