#include "lva.hpp"

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <list>
#include <cassert>
#include <map>

#include "automata/nfa/state.hpp"
#include "factories/factories.hpp"
#include "parse/regex/parser.hpp"

namespace rematch {

// TODO: Copy constructor para LogicalVA (o bien copiar los estados)

LogicalVA::LogicalVA()
    : init_state_(nullptr),
      is_raw_(false),
      v_factory_(std::make_shared<VariableFactory>()),
      f_factory_(std::make_shared<FilterFactory>()) {}

LogicalVA::LogicalVA(uint code) : is_raw_(false) {
  init_state_ = new_state();
  init_state_->setInitial(true);
  State* fstate = new_final_state();

  init_state_->addFilter(code, fstate);
}

LogicalVA::LogicalVA(const LogicalVA &A)
    : init_state_(new State(*A.init_state_)),
      is_raw_(A.is_raw_),
      v_factory_(A.v_factory_),
      f_factory_(A.f_factory_) {

  // A simple Depth-First Search on the graph of the copied automaton while
  // constructing the copy's graph.

  // Iterative Search using stack for cleanliness in function definitions,
  std::vector<std::pair<State*, State*>> stack;

  for(auto& state: A.states)
    state->tempMark = false;

  stack.push_back(std::make_pair(init_state_, A.init_state_));
  A.init_state_->tempMark = true;

  while(!stack.empty()) {
    auto cpair = stack.back(); stack.pop_back();

    auto new_q = cpair.first;
    auto old_q = cpair.second;

    states.push_back(new_q);
    if(old_q->isFinal) finalStates.push_back(new_q);

    for(auto& filt: old_q->filters) {
      if(filt->next->tempMark) continue;
      State* ns = new State(*filt->next);

      new_q->addFilter(filt->code, ns);

      stack.push_back(std::make_pair(ns, filt->next));
      filt->next->tempMark = true;
    }
    for(auto& cap: old_q->captures) {
      if(cap->next->tempMark) continue;
      State* ns = new State(*cap->next);

      new_q->addCapture(cap->code, ns);

      stack.push_back(std::make_pair(ns, cap->next));
      cap->next->tempMark = true;
    }
    for(auto& eps: old_q->epsilons) {
      if(eps->next->tempMark) continue;
      State* ns = new State(*eps->next);

      new_q->addEpsilon(ns);

      stack.push_back(std::make_pair(ns, eps->next));
      eps->next->tempMark = true;
    }
  }
}

void LogicalVA::set_initial(State* p) {
  init_state_ = p;
  p->setInitial(true);
}

void LogicalVA::set_factories(std::shared_ptr<VariableFactory> v,
										          std::shared_ptr<FilterFactory> f) {
  v_factory_ = v;
  f_factory_ = f;
}

void LogicalVA::adapt_capture_jumping() {
  std::vector<State*> stack;
  State *reached_state;

  for(auto &state: states) {
    for(auto &state2: states) {
      state2->tempMark = false;
    }
    stack.clear();

    for(auto &capture: state->captures) {
      stack.push_back(capture->next);
      state->tempMark = false;
    }

    while(!stack.empty()) {
      reached_state = stack.back();
      stack.pop_back();

      reached_state->tempMark = true;

      if(!reached_state->filters.empty() || !reached_state->epsilons.empty() || reached_state->isFinal)
        state->addEpsilon(reached_state);
      for(auto &capture: reached_state->captures) {
        if(!capture->next->tempMark)
          stack.push_back(capture->next);
      }
    }
  }

  for(auto &state: states)
    state->captures.clear();

  is_raw_ = true;
}

void LogicalVA::cat(LogicalVA &a2) {
  /* Concatenates an LogicalVA a2 to the current LogicalVA (inplace) */

  // Adds eps transitions from final states to a2 init State
  for(std::size_t i=0;i<finalStates.size();i++){
    finalStates[i]->addEpsilon(a2.init_state_);
    finalStates[i]->setFinal(false);
  }

  a2.init_state_->setInitial(false);

  // Add a2 states to states list
  states.insert(states.end(), a2.states.begin(), a2.states.end());

  // Set a2 final states as new final states
  finalStates.clear();
  finalStates = a2.finalStates;
}

void LogicalVA::alter(LogicalVA &a2) {
  /* Extends the LogicalVA so it can alternate between itself and an
     LogicalVA a2 */

  // Creates a new init State and connects it to the old init and a2's init
  State* newinitState = new State();
  newinitState->addEpsilon(init_state_);
  newinitState->addEpsilon(a2.init_state_);

  init_state_->setInitial(false);

  init_state_ = newinitState;

  init_state_->setInitial(true);

  states.push_back(init_state_);
  // Add a2 final states to final states list
  finalStates.insert(finalStates.end(),
    a2.finalStates.begin(), a2.finalStates.end());

  // Add a2 states to states list
  states.insert(states.end(), a2.states.begin(), a2.states.end());
}

void LogicalVA::kleene() {
  /* Extends the LogicalVA for kleene closure (0 or more times) */

  if(states.size() == 2 && init_state_->filters.size() == 1) {
    if(init_state_->filters.front()->next->isFinal) {
      for(auto it=states.begin(); it != states.end(); it++) {
        if(!(*it)->isInit) {
          states.erase(it); break;
        }
      }

      auto fcode = init_state_->filters.front()->code;
      init_state_->filters.clear();

      init_state_->addFilter(fcode, init_state_);
      finalStates.clear();
      finalStates.push_back(init_state_);
      init_state_->setFinal(true);
      return;
    }
  }

  // Connect final states to new init State
  for(std::size_t i=0;i<finalStates.size();i++){
    finalStates[i]->addEpsilon(init_state_);
    finalStates[i]->setFinal(false);
  }

  // Set new init as the final State
  finalStates.clear();
  finalStates.push_back(init_state_);
  init_state_->setFinal(true);
}

void LogicalVA::strict_kleene() {
  /* Extends the LogicalVA for strict kleene closure (1 or more times) */

  // Connect final states to init State
  for(std::size_t i=0;i<finalStates.size();i++){
    finalStates[i]->addEpsilon(init_state_);
  }
}

void LogicalVA :: optional() {
  /* Extends the LogicalVA for optional closure (0 or 1 time) */

  // Set new init as a final State
  if (!init_state_->isFinal)
  {
    finalStates.push_back(init_state_);
    init_state_->setFinal(true);
  }
}

void LogicalVA::assign(std::bitset<32> open_code, std::bitset<32> close_code) {
  /* Extends the LogicalVA so it can assign its pattern to a variable */

  // Create new states
  State* openLVAState = new_state();
  State* closeLVAState = new_state();

  // Connect new open State with init State
  openLVAState->addCapture(open_code, init_state_);

  init_state_->setInitial(false);

  // Set open State as new init State
  init_state_ = openLVAState;

  init_state_->setInitial(true);

  // Connect final states with new close State
  for(std::size_t i=0;i<finalStates.size();i++){
    finalStates[i]->addCapture(close_code, closeLVAState);
    finalStates[i]->setFinal(false);
  }

  // Set close State as the only final State
  finalStates.clear();
  finalStates.push_back(closeLVAState);
  closeLVAState->setFinal(true);
}

void LogicalVA::repeat(int min, int max) {
  // std::cout << pprint() << "\n\n";
  LogicalVA copied(*this);
  if (min == 0 && max == -1) {
    kleene(); return;
  }

  for(int i=1; i < min-1; i++) {
    LogicalVA copied_automaton(copied);
    cat(copied_automaton);
  }

  if(min > 1) {
    LogicalVA copied_automaton(copied);
    if(max == -1)
      copied_automaton.strict_kleene();
    cat(copied_automaton);
  }

  // This is the optional part
  if(max-min > 0) {
    LogicalVA *copied_automaton, *copied_automaton2;
    if(min == 0) {
      if(max > 1) {
        copied_automaton = new LogicalVA(copied);
        copied_automaton->optional();
        for(int i=min+1; i < max-1; i++) {
          copied_automaton2 = new LogicalVA(copied);
          copied_automaton2->cat(*copied_automaton);
          copied_automaton2->optional();
          copied_automaton = copied_automaton2;
       }
       cat(*copied_automaton);
       optional();
      } else {
        optional();
      }
    } else {
      copied_automaton = new LogicalVA(copied);
      copied_automaton->optional();
      for(int i=min+1; i < max; i++) {
        copied_automaton2 = new LogicalVA(copied);
        copied_automaton2->cat(*copied_automaton);
        copied_automaton2->optional();
        copied_automaton = copied_automaton2;
      }
      cat(*copied_automaton);
    }
  }

  //  std::cout << pprint() << "\n\n";
}

std::string LogicalVA :: pprint() {
  /* Gives a codification for the LogicalVA that can be used to visualize it
     at https://puc-iic2223.github.io . Basically it uses Breath-First Search
     to get every labeled transition in the LogicalVA with the unique ids for
     each State */


  // Declarations
  std::stringstream ss, cond;
  State *current;
  int cid, nid;  // cid: current State id; nid : next State id
  std::bitset<32> S;

  std::vector<int> capture_states, pcapture_states;

  // Typical set construction for keeping visited states
  std::unordered_set<unsigned int> visited;

  // Use of list to implement a FIFO queue
  std::list<State*> queue;

  // Start on the init State
  visited.insert(init_state_->id);
  queue.push_back(init_state_);

  // Start BFS
  while(!queue.empty()) {
    current = queue.front();
    queue.pop_front();
    cid = current->id;

    if(current->flags() & State::kCaptureState)
			capture_states.push_back(current->id);
    if(current->flags() & State::kPreCaptureState)
			pcapture_states.push_back(current->id);

    // For every epsilon transition
    for (auto &epsilon: current->epsilons) {
      nid = epsilon->next->id;

      ss << "t " << cid << " eps " << nid << '\n';

      // If not visited enqueue and add to visited
      if (visited.find(nid) == visited.end()) {
        visited.insert(nid);
        queue.push_back(epsilon->next);
      }
    }

    // For every capture transition
    for (auto &capture: current->captures) {
      S = capture->code;

      nid = capture->next->id;

      ss << "t " << cid << " " << v_factory_->print_varset(S) << " " << nid << '\n';

      // If not visited enqueue and add to visited
      if (visited.find(nid) == visited.end()) {
        visited.insert(nid);
        queue.push_back(capture->next);
      }
    }

    // For every filter transition
    for (auto &filter: current->filters) {
      nid = filter->next->id;
      S = filter->code;

      // TODO: Get the correct transition name

      ss << "t " << cid << ' ' << f_factory_->get_filter(filter->code) << ' ' << nid << '\n';

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

  // Code initial State
  ss << "i " << init_state_->id;

  // for(int id: capture_states)
	// 	ss << "\nc " << id;

  // for(int id: pcapture_states)
	// 	ss << "\npc " << id;

  return ss.str();
}

State* LogicalVA::new_state() {
  State *nstate = new State();
  states.push_back(nstate);

  return nstate;
}

State* LogicalVA::new_final_state() {
  State *nstate = new State();
  states.push_back(nstate);

  finalStates.push_back(nstate);
  nstate->setFinal(true);

  return nstate;
}

} // end namespace rematch