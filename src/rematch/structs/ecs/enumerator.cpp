#include "enumerator.hpp"

#include <bitset>
#include <iostream>
#include <sstream>

#include "factories/factories.hpp"
#include "match.hpp"
#include "regex/regex.hpp"
#include "structs/dag/fastnodelist.hpp"
#include "structs/dag/node.hpp"
#include "structs/dag/nodelist.hpp"

namespace rematch {
namespace internal {

Enumerator::Enumerator(RegEx &r)
    : var_factory_(r.vfactory()) { }

Match_ptr Enumerator::next() {
  while (!stack_.empty()) {
    EnumState current_state = stack_.back();
    ECS::Node *current_node = current_state.node;
    MatchData &current_mapping = current_state.current_mapping;

    stack_.pop_back();

    if (current_node->is_bottom()) {
      tot_mappings_++;
      Match_ptr ret(new Match(var_factory_, current_mapping));
      return ret;
    }

    if (current_node->is_output()) {  // If label node
      internal::ECS::Data dt = current_node->data();
      for (size_t j = var_factory_->size() * 2; j-- > 0;) {
        if (dt.S[j]) {
          current_mapping[dt.i - var_factory_->get_offset(j)][j] = 1;
        }
        // TODO: Hacer una version con/sin offset dependiendo del automata
      }
      stack_.emplace_back(current_node->next(), current_mapping);
    } else {  // If union node
      stack_.emplace_back(current_node->right(), current_mapping);
      stack_.emplace_back(current_node->left(), current_mapping);
    }
  }  // end while()

  throw std::exception();
}

}  // end namespace internal

}  // end namespace rematch
