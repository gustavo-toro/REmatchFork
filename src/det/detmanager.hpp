#ifndef DETMANAGER_HPP
#define DETMANAGER_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include <bitset>

#include "bitsetwrapper.hpp"
#include "det/setstate.hpp"
#include "automata/detautomaton.hpp"
#include "automata/detstate.hpp"
#include "anchors.hpp"

class DetManager {

	using DFAStatesTable = std::unordered_map<BitsetWrapper, DetState*>;
	using VectorCharTable = std::unordered_map<BitsetWrapper, std::vector<char>>;

 public:
	DetManager(const std::string pattern, Anchor anchor=kBothAnchors, bool raw_automata=false);

	DetState* reachAnchoredState(DetState* state, int anchor_code);
	DetState* getNextSubset(SetState* ss, BitsetWrapper charBitset);
	void computeCaptures(DetState* q);
	void computeFullDetAutomaton();
  void computeFullDetAutomatonSingles();
	DetState* getNextDetState(DetState* s, BitsetWrapper charBitset);
	DetState* getNextDetState(DetState* &s, char a, size_t idx);
	DetState* getNextDetState(DetState* s, char32_t a);
	BitsetWrapper applyFilters(char32_t a);

	std::string uniformSample(size_t n);
	char chooseFromCharBitset(BitsetWrapper bs);

	std::shared_ptr<VariableFactory> varFactory() const {return variable_factory_;}
	std::shared_ptr<FilterFactory> filterFactory() const {return filter_factory_;}

	DetAutomaton& DFA() {return *dfa_;}

	void set_anchor(Anchor anchor);

 private:
	void init_dfa();
	void init_automata();

	const std::string pattern_;

	// ExtendedVA representation of the given pattern.
	std::unique_ptr<ExtendedVA> nfa_;

	// Determinization of the eVA computed on-the-fly.
	std::unique_ptr<DetAutomaton> dfa_;

	// Access to regex's factories
	std::shared_ptr<VariableFactory> variable_factory_;
	std::shared_ptr<FilterFactory> filter_factory_;

	Anchor anchor_;

	// Hash table for the mapping between bitstring subset representation of
	// NFA states to DFA states
	DFAStatesTable dstates_table_;

	VectorCharTable all_chars_table_;

	// Wether or not the stored automata is raw (i.e. without variables)
	bool raw_automata_;
};

#endif

