#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <list>
#include <cassert>
#include <map>

#include "lva.hpp"
#include "structures.hpp"
#include "lvastate.hpp"
#include "factories/factories.hpp"
#include "parser/parser.hpp"

LogicalVA :: LogicalVA()
    : init_state_(new LVAState()),
      v_factory_(std::make_shared<VariableFactory>()),
      f_factory_(std::make_shared<FilterFactory>()) {
  init_state_->setInitial(true);
  states.push_back(init_state_);
}

LogicalVA :: LogicalVA(vf_sptr vf, ff_sptr ff)
     : init_state_(new LVAState()),
      v_factory_(vf),
      f_factory_(ff) {
  init_state_->setInitial(true);
  states.push_back(init_state_);
}

LogicalVA :: LogicalVA(const char &a) {
  init_state_ = new LVAState();
  states.push_back(init_state_);

  LVAState* fState = new LVAState();
  finalStates.push_back(fState);
  states.push_back(fState);
  fState->setFinal(true);

  int coding = 1;

   // Connect initState with fState
  init_state_->addFilter(coding, fState);
}

LogicalVA :: LogicalVA(const char &a, vf_sptr vf, ff_sptr ff)
     : init_state_(new LVAState()),
      v_factory_(vf),
      f_factory_(ff) {
  init_state_->setInitial(true);
  states.push_back(init_state_);

  LVAState* fState = new LVAState();
  finalStates.push_back(fState);
  states.push_back(fState);
  fState->setFinal(true);

  int coding = f_factory_->getCode(a);

  // Connect initState with fState
  init_state_->addFilter(coding, fState);
}

LogicalVA :: LogicalVA(int spec, bool negated, vf_sptr vf, ff_sptr ff)
     : init_state_(new LVAState()),
      v_factory_(vf),
      f_factory_(ff) {
  init_state_->setInitial(true);
  states.push_back(init_state_);

  LVAState* fState = new LVAState();
  finalStates.push_back(fState);
  states.push_back(fState);
  fState->setFinal(true);

  int coding = f_factory_->getCode(CharClass(spec, negated));

  // Connect initState with fState
  init_state_->addFilter(coding, fState);
}

LogicalVA::LogicalVA(const LogicalVA &A)
  : init_state_(new LVAState(*A.init_state_)),
    v_factory_(A.v_factory_),
    f_factory_(A.f_factory_) {

  states.push_back(init_state_);

  // A simple Depth-First Search on the graph of the copied automaton while
  // constructing the copy's graph.

  // Iterative Search using stack for cleaness in function definitions,
  std::vector<std::pair<LVAState*, LVAState*>> stack_;

  for(auto& state: A.states)
    state->tempMark = false;

  stack_.push_back(std::make_pair(init_state_, A.init_state_));
  A.init_state_->tempMark = true;

  while(!stack_.empty()) {
    auto cpair = stack_.back(); stack_.pop_back();

    for(auto& filt: cpair.second->f) {
      if(filt->next->tempMark) continue;
      LVAState* ns = new LVAState(*filt->next);

      this->states.push_back(ns);
      if(ns->isFinal) this->finalStates.push_back(ns);

      cpair.first->addFilter(filt->code, ns);

      stack_.push_back(std::make_pair(ns, filt->next));
      filt->next->tempMark = true;
    }
    for(auto& cap: cpair.second->c) {
      if(cap->next->tempMark) continue;
      LVAState* ns = new LVAState(*cap->next);

      this->states.push_back(ns);
      if(ns->isFinal) this->finalStates.push_back(ns);

      cpair.first->addCapture(cap->code, ns);

      stack_.push_back(std::make_pair(ns, cap->next));
      cap->next->tempMark = true;
    }
    for(auto& eps: cpair.second->e) {
      if(eps->next->tempMark) continue;
      LVAState* ns = new LVAState(*eps->next);

      this->states.push_back(ns);
      if(ns->isFinal) this->finalStates.push_back(ns);

      cpair.first->addEpsilon(ns);

      stack_.push_back(std::make_pair(ns, eps->next));
      eps->next->tempMark = true;
    }
  }
}

void LogicalVA::adapt_anchors(Anchor &anchor) {
  if(anchor == Anchor::kBothAnchors)
    return;

  auto anychar_code = f_factory_->addFilter(CharClass(ANYCHAR, false));
  // Need to unanchor the final states
  for(auto &state: finalStates) {
    state->addFilter(anychar_code, state);
  }
  if(anchor == Anchor::kUnanchored) {
    // Need to unanchor the begining
	  init_state_->addFilter(anychar_code, init_state_);
  }
}

void LogicalVA::adapt_capture_jumping() {
  std::vector<LVAState*> stack;
  LVAState *reached_state;


  for(auto &state: states) {
    stack.clear();

    for(auto &capture: state->c) {
      stack.push_back(capture->next);
      state->tempMark = false;
    }

    while(!stack.empty()) {
      reached_state = stack.back();
      stack.pop_back();

      reached_state->tempMark = true;

      if(!reached_state->f.empty() || !reached_state->e.empty() || reached_state->isFinal)
        state->addEpsilon(reached_state);
      for(auto &capture: reached_state->c) {
        if(!reached_state->tempMark)
          stack.push_back(capture->next);
      }
    }
  }

  for(auto &state: states)
    state->c.clear();
}

void LogicalVA::cat(LogicalVA &a2) {
  /* Concatenates an LogicalVA a2 to the current LogicalVA (inplace) */

  // TODO: Check if var sets set of both automata is disjunct

  // Adds eps transitions from final states to a2 init LVAState
  for(std::size_t i=0;i<finalStates.size();i++){
    finalStates[i]->addEpsilon(a2.init_state_);
    finalStates[i]->setFinal(false);
  }

  // Add a2 states to states list
  states.insert(states.end(), a2.states.begin(), a2.states.end());

  // Set a2 final states as new final states
  finalStates.clear();
  finalStates = a2.finalStates;
}

void LogicalVA::alter(LogicalVA &a2) {
  /* Extends the LogicalVA so it can alternate between itself and an
     LogicalVA a2 */

  // TODO: Check if var sets of both automata is the same

  // Creates a new init LVAState and connects it to the old init and a2's init
  LVAState* newinitState = new LVAState();
  newinitState->addEpsilon(init_state_);
  newinitState->addEpsilon(a2.init_state_);

  init_state_ = newinitState;

  states.push_back(init_state_);
  // Add a2 final states to final states list
  finalStates.insert(finalStates.end(),
    a2.finalStates.begin(), a2.finalStates.end());

  // Add a2 states to states list
  states.insert(states.end(), a2.states.begin(), a2.states.end());
}

void LogicalVA :: kleene() {
  /* Extends the LogicalVA for kleene closure (0 or more times) */

  if(states.size() == 2 && init_state_->f.size() == 1) {
    if(init_state_->f.front()->next->isFinal) {
      for(auto it=states.begin(); it != states.end(); it++) {
        if(!(*it)->isInit) {
          states.erase(it); break;
        }
      }

      auto fcode = init_state_->f.front()->code;
      init_state_->f.clear();

      init_state_->addFilter(fcode, init_state_);
      finalStates.clear();
      finalStates.push_back(init_state_);
      init_state_->setFinal(true);
      return;
    }
  }

  // Connect final states to new init LVAState
  for(std::size_t i=0;i<finalStates.size();i++){
    finalStates[i]->addEpsilon(init_state_);
    finalStates[i]->setFinal(false);
  }

  // Set new init as the final LVAState
  finalStates.clear();
  finalStates.push_back(init_state_);
  init_state_->setFinal(true);
}

void LogicalVA :: strict_kleene() {
  /* Extends the LogicalVA for strict kleene closure (1 or more times) */

  // Connect final states to init LVAState
  for(std::size_t i=0;i<finalStates.size();i++){
    finalStates[i]->addEpsilon(init_state_);
  }
}

void LogicalVA :: optional() {
  /* Extends the LogicalVA for optional closure (0 or 1 time) */

  // Set new init as a final LVAState
  if (!init_state_->isFinal)
  {
    finalStates.push_back(init_state_);
    init_state_->setFinal(true);
  }
}

void LogicalVA::repeat(int min, int max) {
  LogicalVA copied(*this);
  if(min == 0 && max > 0) {
    optional();
  } else if (min == 0 && max == -1) {
    kleene();
  } else if (min == 1 && max == -1) {
    strict_kleene();
  }

  for(int i=1; i < min-1; i++) {
    LogicalVA copied_automaton(copied);
    cat(copied_automaton);
  }

  // Last one may be a loop
  if(min > 1) {
    LogicalVA copied_automaton(copied);
    if(max == -1)
      copied_automaton.strict_kleene();
    cat(copied_automaton);
  }

  for(int i=(min <= 1)? 1 :min; i < max; i++) {
    LogicalVA copied_automaton(copied);
    copied_automaton.optional();
    cat(copied_automaton);
  }
}

void LogicalVA :: assign(std::string varName) {
  /* Extends the LogicalVA so it can assign its pattern to a variable */

  // TODO: Check if new var is not in the vars set of the LogicalVA

  // Create new states
  LVAState* openLVAState = new LVAState();
  LVAState* closeLVAState = new LVAState();

  // Add new states to states list
  states.push_back(openLVAState);
  states.push_back(closeLVAState);

  std::bitset<32> openCoding, closeCoding;
  openCoding = v_factory_->getOpenCode(varName);
  closeCoding = v_factory_->getCloseCode(varName);

  // Connect new open LVAState with init LVAState
  openLVAState->addCapture(openCoding, init_state_);

  // Set open LVAState as new init LVAState
  init_state_ = openLVAState;

  // Connect final states with new close LVAState
  for(std::size_t i=0;i<finalStates.size();i++){
    finalStates[i]->addCapture(closeCoding, closeLVAState);
    finalStates[i]->setFinal(false);
  }

  // Set close LVAState as the only final LVAState
  finalStates.clear();
  finalStates.push_back(closeLVAState);
  closeLVAState->setFinal(true);
}

std::string LogicalVA :: pprint() {
  /* Gives a codification for the LogicalVA that can be used to visualize it
     at https://puc-iic2223.github.io . Basically it uses Breath-First Search
     to get every labeled transition in the LogicalVA with the unique ids for
     each LVAState */


  // Declarations
  std::stringstream ss, cond;
  LVAState *current;
  int cid, nid;  // cid: current LVAState id; nid : next LVAState id
  std::bitset<32> S;



  // Typical set construction for keeping visited states
  std::unordered_set<unsigned int> visited;

  // Use of list to implement a FIFO queue
  std::list<LVAState*> queue;

  // Start on the init LVAState
  visited.insert(init_state_->id);
  queue.push_back(init_state_);



  // Start BFS
  while(!queue.empty()) {
    current = queue.front();
    queue.pop_front();
    cid = current->id;

    // For every epsilon transition
    for (auto &epsilon: current->e) {
      nid = epsilon->next->id;

      ss << "t " << cid << " eps " << nid << '\n';

      // If not visited enqueue and add to visited
      if (visited.find(nid) == visited.end()) {
        visited.insert(nid);
        queue.push_back(epsilon->next);
      }
    }

    // For every capture transition
    for (auto &capture: current->c) {
      S = capture->code;

      nid = capture->next->id;

      ss << "t " << cid << " " << v_factory_->getVarUtil(S) << " " << nid << '\n';

      // If not visited enqueue and add to visited
      if (visited.find(nid) == visited.end()) {
        visited.insert(nid);
        queue.push_back(capture->next);
      }
    }

    // For every filter transition
    for (auto &filter: current->f) {
      nid = filter->next->id;
      S = filter->code;

      // TODO: Get the correct transition name

      ss << "t " << cid << ' ' << f_factory_->getFilter(filter->code).print() << ' ' << nid << '\n';

      // If not visited enqueue and add to visited
      if (visited.find(nid) == visited.end()) {
        visited.insert(nid);
        queue.push_back(filter->next);
      }
    }
  }

  // Code final states
  for (size_t i = 0; i < finalStates.size(); ++i) {
    if(finalStates[i]->isFinal) {
      ss << "f " << finalStates[i]->id << '\n';
    }
  }

  // Code initial LVAState
  ss << "i " << init_state_->id;

  return ss.str();
}