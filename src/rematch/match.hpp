#ifndef MATCH_HPP
#define MATCH_HPP


#include <string>
#include <memory>

#include "factories/factories.hpp"

namespace rematch {

class Match;
class StrDocument;

#ifdef SWIG
  using Match_ptr = Match*;
#else
  using Match_ptr = std::unique_ptr<Match>;
#endif

class Match {
  friend class Enumerator;
  friend class Interface;

 public:

  Match() = default;
  // Match is true if at least ONE variable captured spans
  operator bool() const;
  // Returns a vector with the variable names in order
  // std::vector<std::string> variables() const;
  // Pretty print Match
  std::string pprint(std::shared_ptr<StrDocument>& doc) const;
  // Output format of matches
  friend std::ostream& operator<<(std::ostream &os, Match &m);

 private:
  // Only Enumerator is able to construct a Match
  Match(std::shared_ptr<VariableFactory> vf, std::vector<std::deque<int64_t>> m)
      : var_factory_(vf), data_(m) {}
  // Access to variable names
  std::shared_ptr<VariableFactory> var_factory_;
  // Match main data
  std::vector<std::deque<int64_t>> data_;
};

}


#endif