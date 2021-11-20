#ifndef MATCH_HPP
#define MATCH_HPP


#include <string>
#include <vector>
#include <memory>

#include "evaluation/document/strdocument.hpp"
#include "factories/factories.hpp"

namespace rematch {

class Match;
class StrDocument;

#ifdef SWIG
	using Match_ptr = Match*;
#else
	using Match_ptr = std::unique_ptr<Match>;
#endif

using Span = std::pair<int64_t,int64_t>;
using SpanVec = std::vector<Span>;
using StrVec = std::vector<std::string>;

// Represents a match for easy access to the captured spans and substrings.
// It doesn't store the correspondings substrings, so it's assumed that the
// sublaying document is available.
class Match {
	friend class Enumerator;
	friend class Interface;

 public:

	Match() = default;

	// Match is true if at least ONE variable captured spans
	operator bool() const;

	// Returns a vector with the variable names in order
	std::vector<std::string> variables() const;

	// Returns a variable's captured spans
	SpanVec spans(std::string var) const;

	// Returns the first captured span of a variable
	boost::optional<Span> span(std::string var) const;

	// Returns a variable's captured substrings
	StrVec groups(std::string var, std::shared_ptr<StrDocument>& doc) const;

	// Returns the first captured substring of a variable
	boost::optional<std::string> group(std::string var, std::shared_ptr<StrDocument>& doc) const;

	// para una query de la forma  : !x{}+!y{!x{}}
	// tener estructura árbol de la forma:
	//         root
	//        /    \
	//       x      y
	//               \
	//                x
	// al hacer m.inner_match('x'), retornaría un nuevo Match, filtrando
	// los matches según el árbol (m.spans('y') retornaría un vector vacío):
	//         root
	//          |
	//          x
	// otro ejemplo, m.inner_match('y'), si hago m.spans('x'), no estarán los
	// x pertenecientes a la otra rama del árbol.
	//        root
	//         |
	//         y
	//         |
	//         x
	Match_ptr inner_match(std::string var) const;

	// Pretty print captured substrings
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