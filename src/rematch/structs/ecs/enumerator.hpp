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
    stack_.emplace_back(n, std::vector<int64_t>(var_factory_->size(), 0), MatchData());
  };

  bool has_next() const { return !stack_.empty(); }

  Match_ptr next();

  // TODO: Implement this
  void next(Match* m);

 private:
  // Stores the current node and other state elements
  struct EnumState {
    ECS::Node* node;
    // Counter for trimming each variable deque
    std::vector<int64_t> trim_counter;
    // Ordered map of positions and variables
    MatchData ordered_mapping;

    EnumState(ECS::Node* n, std::vector<int64_t> tc, MatchData om)
        : node(n), trim_counter(tc), ordered_mapping(om) {}
  };  // end struct EnumState

  // Reference to Variable Factory
  std::shared_ptr<VariableFactory> var_factory_;
  // Stack
  std::vector<EnumState> stack_;
  // Each variable has its own container to store spans
  std::vector<std::deque<int64_t>> current_mapping_;

  uint64_t tot_mappings_ = 0;
};  // end class Enumerator

}  // end namespace internal
}  // end namespace rematch

#endif  // STRUCTS__ECS__ENUMERATION_HPP