#ifndef SRC_REMATCH_PARSE_AUTOMATA_WVA_VISITOR_HPP
#define SRC_REMATCH_PARSE_AUTOMATA_WVA_VISITOR_HPP

#include "automata/wnfa/wnfa.hpp"
#include "charclass.hpp"

#include "parse/automata/wva/ast.hpp"
#include "parse/regex/ast.hpp"

#include <bitset>
#include <unordered_map>

#include "parse/charclass/ast.hpp"

namespace rematch {

struct wVAvisitor : boost::static_visitor<void> {
    // LVA to be returned
    ranked::WeightedVA<>* automata;

    // Hash table between state names and state references
    std::unordered_map<std::string, ranked::WeightedVA<>::State*> states_map;

    // Constructor
    wVAvisitor();

    // Internal methods
    ranked::WeightedVA<>::State* get_state(std::string state_name);
    std::bitset<32> get_variable_code(ast::wva::variable const &variable);
    int get_filter_code(ast::atom const &a);

    // Case 1: char transition
    void operator()(ast::wva::weighted_transition const &ct);
    void operator()(ast::wva::state const &s);
};

} // end namespace rematch

#endif // SRC_REMATCH_PARSE_AUTOMATA_WVA_VISITOR_HPP
