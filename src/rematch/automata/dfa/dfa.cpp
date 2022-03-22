#include "dfa.hpp"

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <cassert>
#include <map>
#include <random>
#include <chrono>
#include <iomanip>

#include "structs/dag/nodelist.hpp"
#include "captures.hpp"
#include "factories/factories.hpp"
#include "detstate.hpp"
#include "automata/nfa/eva.hpp"
#include "automata/dfa/transition.hpp"

namespace rematch {

DFA::DFA(VariableFactory* vf)
  : init_state_(new DetState()), variable_factory_(vf)  {states.push_back(init_state_);}

DFA::DFA(ExtendedVA &a)
 : init_state_(new DetState()), variable_factory_(a.varFactory()) {
   states.push_back(init_state_);
}

std::string DFA::pprint() {
  /* Gives a codification for the automaton that can be used to visualize it
     at https://puc-iic2223.github.io . It uses Breath-First Search
     to get every labeled transition in the automaton with the unique ids for
     each state */

  // Declarations
  std::stringstream ss, cond;
  DetState *current;
  std::bitset<32> S;

  // Typical set construction for keeping visited states
  std::unordered_set<unsigned int> visited;

  struct MapElem {
    uint from;
    uint to;
    std::bitset<32> S;

    bool operator==(const MapElem &rhs) const {
      return from == rhs.from && to == rhs.to && S == rhs.S;
    }
  };

  auto MapElemHash = [](const MapElem& el) {
    size_t res = 0;
    boost::hash_combine(res, el.from);
    boost::hash_combine(res, el.to);
    boost::hash_combine(res, el.S.to_ulong());
    return res;
  };

  std::unordered_map<MapElem, CharClassBuilder, decltype(MapElemHash)> table(10, MapElemHash);

  // Use of list to implement a FIFO queue
  std::list<DetState*> queue;

  // Start on the init state
  visited.insert(init_state_->id);
  queue.push_back(init_state_);

  // Start BFS
  while(!queue.empty()) {
    current = queue.front();
    queue.pop_front();
    for (size_t i = 0; i < 128; i++) {
      if(current->transitions_[i] == nullptr) continue;
      auto trans = current->transitions_[i].get();
      if(trans->type_ == 0) continue;
      if(trans->type_ & Transition::Type::kDirect) {// Direct type
        auto ok = table.insert({{current->id, trans->direct_->id, 0}, CharClassBuilder(i)});
        if(!ok.second)
          ok.first->second.add_single(i);
        if (visited.find(trans->direct_->id) == visited.end()) {
          visited.insert(trans->direct_->id);
          queue.push_back(trans->direct_);
        }
      }
      if(trans->type_ & Transition::Type::kSingleCapture) {
        auto ok = table.insert({{current->id, trans->capture_->next->id, trans->capture_->S}, CharClassBuilder(i)});
        if(!ok.second)
          ok.first->second.add_single(i);
        if (visited.find(trans->capture_->next->id) == visited.end()) {
          visited.insert(trans->capture_->next->id);
          queue.push_back(trans->capture_->next);
        }
      } // Single capture
      if(trans->type_ & Transition::Type::kMultiCapture) {
        for(auto &capture: trans->captures_) {
          auto ok = table.insert({{current->id, capture->next->id, capture->S}, CharClassBuilder(i)});
          if(!ok.second)
            ok.first->second.add_single(i);
          if (visited.find(capture->next->id) == visited.end()) {
            visited.insert(capture->next->id);
            queue.push_back(capture->next);
          }
        }
      }
    }
  }

  std::uniform_real_distribution<double> unif(0, 1);

  uint seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng(seed);

  for(auto& el: table) {
    ss << "t " << el.first.from << " {" << el.second << "|(" << variable_factory_->print_varset(el.first.S)
       << ")|"  << std::setprecision(2) << unif(rng) <<  "} "  << el.first.to << '\n';
  }

  // Code final states
  for (size_t i = 0; i < finalStates.size(); ++i) {
    if(finalStates[i]->isFinal) {
      ss << "f " << finalStates[i]->id << " {" << std::setprecision(2) << unif(rng) << "}\n";
    }
  }

  // Code initial state
  ss << "i " << init_state_->id << " {" << std::setprecision(2) << unif(rng) <<'}';

  return ss.str();
}

} // end namespace rematch

