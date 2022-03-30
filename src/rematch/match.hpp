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

	// Given a var, returns the SubMatch of the current Match
	/* USE CASE:
		Match m;
		for (Span &s_table : m.spans("TABLE")) {
			Match m_table = m.submatch(s_table);
			// std::cout << 'table between' << s_table << '\n';
			for (Span &s_row : m_table.spans("ROW")) {
				Match m_row = m_table.submatch(s_row);
				// std::cout << 'row between' << s_row << '\n';
				for (Span &s_cell : m_row.spans("CELL")) {
					// std::cout << 'cell between' << s_cell << '\n';
				}
			}
		}
	*/
	Match submatch(Span s) const;

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