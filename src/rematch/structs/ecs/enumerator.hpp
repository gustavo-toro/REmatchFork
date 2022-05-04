#ifndef STRUCTS__ECS__ENUMERATION_HPP
#define STRUCTS__ECS__ENUMERATION_HPP

#include <bitset>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "factories/factories.hpp"
#include "match.hpp"
#include "memmanager.hpp"
#include "structs/dag/fastnodelist.hpp"
#include "structs/dag/node.hpp"
#include "structs/dag/nodelist.hpp"
#include "structs/ecs/ecs.hpp"

namespace rematch {

class RegEx;

namespace internal {
// Interface for enumerating the DAG-like structure obtained after
// the evaluation step (preprocessing the ourput). It uses the common
// methods next() and hasNext() for obtaining the outputs.
class Enumerator {
 public:
  Enumerator(RegEx& r);

  void add_node(internal::ECS::Node* n) {
    stack_.emplace_back(n, MatchData());
  };

  bool has_next() const { return !stack_.empty(); }

  Match_ptr next();

  // TODO: Implement this
  void next(Match* m);

 private:
  // Stores the current node and other state elements
  struct EnumState {
    ECS::Node* node;
    // Ordered map of positions and variables
    MatchData current_mapping;

    EnumState(ECS::Node* n, MatchData md)
        : node(n), current_mapping(md) {}
  };  // end struct EnumState
  // Reference to Variable Factory
  std::shared_ptr<VariableFactory> var_factory_;
  // Stack
  std::vector<EnumState> stack_;

  uint64_t tot_mappings_ = 0;
};  // end class Enumerator

}  // end namespace internal
}  // end namespace rematch

#endif  // STRUCTS__ECS__ENUMERATION_HPP