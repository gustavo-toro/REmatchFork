#include "enumeration.hpp"

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

Enumerator::Enumerator(RegEx &rgx)
    : var_factory_(rgx.detManager().varFactory()),
      nmappings_(0),
      current_mapping_(var_factory_->size(), std::vector<int64_t>(0)) {}

void Enumerator::addNodeList(internal::NodeList *startList) {
  if (!startList->empty()) {
    depth_stack_.emplace_back(startList->head_, startList->tail_);
  }
}

void Enumerator::addNodeList(internal::FastNodeList *startList) {
  if (!startList->empty()) {
    depth_stack_.emplace_back(startList->start(), startList->end());
  }
}

Match_ptr Enumerator::next() {
  // std::vector<int64_t> current_variables(var_factory_->size() * 2, -1);

  while (!depth_stack_.empty()) {
    auto current = depth_stack_.back();
    internal::Node *node = current.current_node;

    depth_stack_.pop_back();

    if (node->isNodeEmpty()) {
      // SHOW OUTPUT
      for (auto &var_slot : current_mapping_) {
        for (auto &pos : var_slot) {
          std::cout << pos << ' ';
        }
        std::cout << '\n';
      }
      std::cout << "----\n";
      // SHOW OUTPUT
      nmappings_++;
      // MODIFY MATCH.CPP/HPP
      std::unique_ptr<Match> ret(new Match(var_factory_,
                                           std::vector<int64_t>(var_factory_->size() * 2, -2)));
      // MODIFY MATCH.CPP/HPP
      for (auto &m : current_mapping_) m.clear();
      return ret;
    }

    if (node != current.end_node) {
      depth_stack_.emplace_back(node->next, current.end_node);
    }

    if (node->start != nullptr) {
      for (size_t j = 0; j < var_factory_->size() * 2; j++) {
        if (node->S[j])
          current_mapping_[j / 2].push_back(node->i - var_factory_->get_offset(j));
      }

      depth_stack_.emplace_back(node->start, node->end);
    }
  }

  throw std::exception();
}

bool Enumerator ::hasNext() {
  return !depth_stack_.empty();
}

}  // end namespace rematch
