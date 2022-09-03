#ifndef FACTORIES_FACTORIES_HPP
#define FACTORIES_FACTORIES_HPP

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <ostream>
#include <bitset>
#include <map>
#include <utility>

#include "charclass.hpp"

namespace rematch {
// Maximum variables supported
const int MAX_VARS = 15;

// Manager of the parsed RGX formula variables where each variable name
// has a corresponding code.
class VariableFactory {
 public:
	// Simple constructor
	VariableFactory();

	size_t size() {return data_.size();}

	std::string get_var(uint position);

	std::vector<std::string> variables() {return data_;}

	int position(std::string var) const;

	// Add a variable to the struct
	void add(std::string var);

	// Given a variable name outputs the corresponding opening bitset
	std::bitset<32> open_code(std::string var);

	// Given a variable name outputs the corresponding closing bitset
	std::bitset<32> close_code(std::string var);

	// Given a bitset outputs the corresponding opening and closing variables
	// as a std::string
	std::string print_varset(std::bitset<32> code);

	// Prints the hash table
	std::string pprint();

	// Merges the variables present in another VariableFactory inplace
	void merge(VariableFactory &rhs);

	// Checks if a variable name is present
	bool contains(std::string var);

	bool empty();

	// Equality operator overload
	bool operator==(const VariableFactory &vf) const;

	int& get_offset(int index) {return offsetMap[index];}

 private:
	// Ordered vector that stores the variables.
	std::vector<std::string> data_;

	// Offset capturing optimization. Maps each opening and closing
	// capture variable to its computed offset. Then it's a vector of size
	// numVars*2. The vector is such that:
	// 		- offsetMap[2*c]         is the opening (x<) offset.
	//    - offsetMap[2*c + 1] 		 is the closing (x>) offset.
	std::vector<int> offsetMap;

	bool computedOffsets; // True iff offsetMap was computed.
};


// Filter code table. Manages the all CharClassBuilders that are associated with
// a query (we call them Filters for shorthand).
class FilterFactory {
 public:
	// Constructors
	FilterFactory();

	size_t size() const {return size_;}

	std::string pprint();

	std::unordered_map<std::vector<bool>, std::vector<char>> allPossibleCharBitsets();

	// Adds a CharClassBuilder to the factor and returns its associated code.
	// If already present then just returns the associated code.
	int add_filter(CharClassBuilder ccb);

	// Given a CharClassBuilder, gets the associated code.
	int get_code(CharClassBuilder ccb);

	// Given a code, gets the associated CharClassBuilder.
	CharClassBuilder& get_filter(int code);

	// Check if a CharClassBuilder is already present in the factory.
	bool contains(CharClassBuilder &ccb) const;

	// Merges the Factory with another one inplace.
	void merge(FilterFactory &rest);

	std::vector<bool> applyFilters(char a);

 private:
	size_t size_ = 0;
	// Ordered vector that stores the variables.
	std::unordered_map<CharClassBuilder, char> code_map_;
	std::unordered_map<char, CharClassBuilder> filter_map_;
	// Char (document-readed) -> Bitset hash table
	std::unordered_map<char, std::vector<bool>> bitsetMap;
};

} // end namespace rematch

#endif // FACTORIES_FACTORIES_HPP
