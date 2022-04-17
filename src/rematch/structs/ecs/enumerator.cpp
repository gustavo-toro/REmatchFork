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
    : var_factory_(r.vfactory()),
      current_mapping_(var_factory_->size(), std::deque<int64_t>(0)) { }

Match_ptr Enumerator::next() {
  while (!stack_.empty()) {
    EnumState current_state = stack_.back();
    ECS::Node *current_node = current_state.node;
    std::vector<int64_t> &trim_counter = current_state.trim_counter;
    
    stack_.pop_back();

    // Trim each variable array from the right
    for (size_t j = 0; j < var_factory_->size(); j++)
      current_mapping_[j].erase(current_mapping_[j].begin(), current_mapping_[j].end() - trim_counter[j]);

    if (current_node->is_bottom()) {
      tot_mappings_++;
      Match_ptr ret(new Match(var_factory_, current_mapping_));
      return ret;
    }

    if (current_node->is_output()) {  // If label node
      internal::ECS::Data dt = current_node->data();
      for (size_t j = var_factory_->size() * 2; j-- > 0 ;) {
        if (dt.S[j]) {
          current_mapping_[j / 2].push_front(dt.i - var_factory_->get_offset(j));
          trim_counter[j / 2]++;
        }
        // TODO: Hacer una version con/sin offset dependiendo del automata
      }

      stack_.emplace_back(current_node->next(), trim_counter);
    } else {  // If union node
      stack_.emplace_back(current_node->right(), trim_counter);
      stack_.emplace_back(current_node->left(), trim_counter);
    }
  }  // end while()

  throw std::exception();
}

}  // end namespace internal

}  // end namespace rematch
