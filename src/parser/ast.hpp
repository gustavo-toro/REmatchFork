/*
Author:
    nicovsj
Description:
    Module defining the structs used at parsing-time.
*/

#ifndef AST_HPP
#define AST_HPP

#include <set>
#include <vector>
#include <string>
#include <iostream>

#include <boost/fusion/adapted.hpp>
#include <boost/variant.hpp>     // for tree nodes
#include <boost/optional.hpp>    // for multiplicity upperbound

using std::vector;

namespace ast {

struct charset {
    /* Struct for class of char information containment */

    bool negated;  // Is a negated charset ?

    using range = std::tuple<char, char>;
    using element = boost::variant<char, range>;

    std::set<element> elements;
};

// Special classes
struct anychar {friend std::ostream& operator<<(std::ostream& os, const anychar& a);};
struct anydigit {friend std::ostream& operator<<(std::ostream& os, const anydigit& a);};
struct nondigit {friend std::ostream& operator<<(std::ostream& os, const nondigit& a);};
struct anyword {friend std::ostream& operator<<(std::ostream& os, const anyword& a);};
struct nonword {friend std::ostream& operator<<(std::ostream& os, const nonword& a);};
struct anywhitespace {friend std::ostream& operator<<(std::ostream& os, const anywhitespace& a);};
struct nonwhitespace {friend std::ostream& operator<<(std::ostream& os, const nonwhitespace& a);};

// Recursive structs
struct parenthesis;
struct assignation;

struct anchor {
    anchor() = default;

    anchor(bool b): is_start(b) {}

    bool is_start;
};

// Atom
using atom = boost::variant<charset, anchor, char, anychar, anydigit, nondigit,
                        anyword, nonword, anywhitespace, nonwhitespace>;
// Group
using group =  boost::variant<
    boost::recursive_wrapper<parenthesis>,
    boost::recursive_wrapper<assignation>,
    atom>;


struct repetition {
    repetition(int s, int e): start_(s), end_(e) {}

    repetition(): start_(-1), end_(-1) {}

    int start_;
    int end_;
};



// Iter
struct iter {
    group expr;
    std::vector<repetition> repetitions;
};

// Concat and altern
using concat = std::vector<iter>;
using altern = std::vector<concat>;

struct parenthesis {
    altern root;

    parenthesis() = default;

    parenthesis(altern root): root(std::move(root)) {}

    friend std::ostream& operator<<(std::ostream& os, const parenthesis& p);
};

struct assignation {
    std::string var;

    altern root;

    assignation() = default;

    assignation(std::string var, altern root): var(var), root(std::move(root)) {}
};

} // end namespace ast


BOOST_FUSION_ADAPT_STRUCT(ast::charset,
        (bool, negated)
        (std::set<ast::charset::element>, elements))

BOOST_FUSION_ADAPT_STRUCT(ast::iter,
        (ast::group, expr)
        (std::vector<ast::repetition>, repetitions))

BOOST_FUSION_ADAPT_STRUCT(ast::assignation,
        (std::string, var)
        (ast::altern, root))

#endif