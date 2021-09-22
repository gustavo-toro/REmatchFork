#include "enumeration.hpp"

#include <iostream>
#include <sstream>
#include <bitset>

#include "match.hpp"
#include "structs/dag/node.hpp"
#include "structs/dag/nodelist.hpp"
#include "structs/dag/fastnodelist.hpp"
#include "factories/factories.hpp"
#include "regex/regex.hpp"

namespace rematch {

Enumerator::Enumerator(RegEx &rgx)
    : var_factory_(rgx.detManager().varFactory()),
      nmappings_(0),
      current_mapping_(0, std::vector<int64_t>(0)) {}


void Enumerator::addNodeList(internal::NodeList *startList) {
  if(!startList->empty()){
    depth_stack_.emplace_back(startList->head_, startList->tail_);
  }
}

void Enumerator::addNodeList(internal::FastNodeList *startList) {
  if(!startList->empty()){
    depth_stack_.emplace_back(startList->start(), startList->end());
  }
}

Match_ptr Enumerator::next() {
  std::vector<int64_t> current_submapping(var_factory_->size() * 2, -1);
  while(!depth_stack_.empty()) {
    auto current = depth_stack_.back();
    internal::Node* node = current.current_node;

    depth_stack_.pop_back();

    if(node->isNodeEmpty()) {
      nmappings_++;
      std::unique_ptr<Match> ret(new Match(var_factory_, current_mapping_[0]));
      // reset current_mapping
      current_mapping_.clear();
      return ret;
    }

    if(node != current.end_node) {
      depth_stack_.emplace_back(node->next, current.end_node);
    }

    if(node->start != nullptr) {
      for(size_t j=0; j < var_factory_->size() * 2; j++) {
        if(node->S[j])
          current_submapping[j] =  node->i - var_factory_->get_offset(j);
      }

      if (std::find(current_submapping.begin(), current_submapping.end(), -1) == current_submapping.end()) {
        // if it's filled
        current_mapping_.push_back(current_submapping);
        // reset current_submapping
        std::fill(current_submapping.begin(), current_submapping.end(), -1);
      }

      depth_stack_.emplace_back(node->start, node->end);
    }

  }

  throw std::exception();
}


bool Enumerator :: hasNext() {
  return !depth_stack_.empty();
}

} // end namespace rematch

