#ifndef SRC_REMATCH_PARSE_AUTOMATA_WVA_AST_HPP
#define SRC_REMATCH_PARSE_AUTOMATA_WVA_AST_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/optional.hpp>

#include <string>

#include <set>
#include <vector>
#include <string>

#include "parse/regex/ast.hpp"
#include "parse/charclass/ast.hpp"


namespace rematch {
namespace ast {
namespace wva {

  enum class StateType { kInit, kAccepting };

  enum class CaptureType { kOpen, kClose };

  struct variable {
    std::string name;
    CaptureType type;
  };

  struct state {
    std::string label;
    StateType type;
    double weight;
  };

  struct weighted_transition {
    std::string from_state;
    ast::atom text;
    std::vector<variable> variables;
    double weight;
    std::string to_state;
  };

  using any = boost::variant<weighted_transition,state>;

} // end namespace wva
} // end namespace ast
} // end namespace rematch

// We need to tell fusion about our structs
// to make them a first-class fusion. This has to
// be in global scope.

BOOST_FUSION_ADAPT_STRUCT(
  rematch::ast::wva::variable,
  (std::string, name)
  (rematch::ast::wva::CaptureType, type)
)

BOOST_FUSION_ADAPT_STRUCT(
  rematch::ast::wva::state,
  (std::string, label)
  (rematch::ast::wva::StateType, type)
  (double, weight)
)

BOOST_FUSION_ADAPT_STRUCT(
  rematch::ast::wva::weighted_transition,
  (std::string, from_state)
  (rematch::ast::atom, text)
  (std::vector<rematch::ast::wva::variable>, variables)
  (double, weight)
  (std::string, to_state)
)

#endif // SRC_REMATCH_PARSE_AUTOMATA_WVA_AST_HPP
