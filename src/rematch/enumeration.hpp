#ifndef ENUMERATION_H
#define ENUMERATION_H

#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <deque>
#include <string>
#include <stack>
#include <utility>
#include <memory>

#include "match.hpp"
#include "structs/dag/nodelist.hpp"
#include "structs/dag/fastnodelist.hpp"
#include "structs/dag/node.hpp"
#include "factories/factories.hpp"
#include "memmanager.hpp"

namespace rematch {

class RegEx;

// Interface for enumerating the DAG-like structure obtained after
// the evaluation step (preprocessing the ourput). It uses the common
// methods next() and hasNext() for obtaining the outputs.
class Enumerator {

  friend class Evaluator;

  public:
    Enumerator(RegEx &rgx);

    // Get the next match according to the current state of the depth stack.
    Match_ptr next();

    // Returns if there is a next match according to the current state of
    // the depth stack.
    bool hasNext();

    // Adds a NodeList to the depth stack. So it's outputs get enumerated
    // in the future.
    void addNodeList(internal::NodeList *nl);
    void addNodeList(internal::FastNodeList *nl);

    // Resets the enumeration.
    void reset() {depth_stack_.clear();}

    // Returns the total number of mappings

 private:

  // Elements of the depth stack of the enumeration.
  struct EnumState {
    internal::Node* current_node;    // Current Node of the state of the enumeration.
    internal::Node* end_node;        // Needed to know when to stop while going down
    std::vector<size_t> last_indexes;

    EnumState(internal::Node* c, internal::Node* e, std::vector<size_t> li)
      : current_node(c), end_node(e), last_indexes(li) {}
  }; // end struct EnumeratorNode

  std::shared_ptr<VariableFactory> var_factory_;

  std::vector<EnumState> depth_stack_;  // Stack for DFS in the mappingDAG

  // stores a deque of spans for each variable
  std::vector<std::deque<int64_t>> current_mapping_;
}; // end class Enumerator

} // end namespace rematch

#endif // ENUMERATION_H