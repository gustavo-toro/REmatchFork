#ifndef CHARCLASS_HPP
#define CHARCLASS_HPP

#include <set>
#include <string>
#include <tuple>
#include <locale>

#include "parser/ast.hpp"

// Enum for special character classes (e.g. NONDIGIT = [^0-9])
enum special {
	ANYCHAR=1,
	ANYDIGIT=2,
	ANYWORD=3,
	ANYSPACE=4,
	kStartAnchor,
	kEndAnchor
};

// TODO: Inherit special charclasses

class CharClass {
	/* Extension of ast::charset (parsing struct) that stores the information of a
	   regex charclass (e.g [^a-zA-Z0-9]) */


	public:
		using range = std::tuple<char32_t,char32_t>;
		using special_code = std::tuple<std::string, bool, int>;

		static const std::set<special_code> special_codes;

		int special;
		bool negated;
		std::string label;
		std::set<range> ranges;
		std::set<char32_t> singles;


		// Empty constructor
		CharClass();

		// Single char constructor
		CharClass(const char32_t &a);

		// Special sets constructor
		CharClass(int special, bool negated);

		// Regex grammar charset constructor
		CharClass(const ast::charset &cs);

		// General costructor
		CharClass(std::string label, bool is_special);

		// Charset constructor
		CharClass(bool negated, std::set<range> ranges, std::set<char32_t> singles);


	bool operator==(const CharClass& rhs) const;

	std::string print();

	void updateLabel();

	bool check(char32_t a);
};


// Hashing for the class
namespace std {
template <>
	struct hash<CharClass> {
		size_t operator()(const CharClass& ch) const {
			hash<string> hasher;
			return hasher(ch.label);
			}
		};
}

#endif