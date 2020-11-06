#include "eval.hpp"

#include "automata/detstate.hpp"
#include "memmanager.hpp"

namespace rematch {

Evaluator::Evaluator(RegEx &rgx, std::istream& input,
                     uint8_t flags)
    : rgx_(&rgx),
      text_(std::make_unique<FileDocument>(input)),
      early_output_(flags & kEarlyOutput),
      line_by_line_(flags & kLineByLine),
      document_ended_(false),
      direct_text_(false),
      i_pos_(0),
      i_start_(0),
      nlines_(0),
      capture_counter_(0),
      reading_counter_(0) {
  init();
}

Evaluator::Evaluator(RegEx &rgx, const std::string &text,
                     uint8_t flags)
    : rgx_(&rgx),
      text_(std::make_unique<StrDocument>(text)),
      early_output_(flags & kEarlyOutput),
      line_by_line_(flags & kLineByLine),
      document_ended_(false),
      direct_text_(true),
      i_pos_(0),
      i_start_(0),
      nlines_(0),
      capture_counter_(0),
      reading_counter_(0) {
  // std::cout << "[Eval] Evaluator() init with StrDocument\n";
  init();
}

void Evaluator::init() {
  std::string str_ = "";
  enumerator_ = std::make_unique<Enumerator>(rgx_, str_);
  if(line_by_line_) {
    text_->getline(line_);
    line_ += '\n';
    nlines_++;
  }
  initAutomaton(i_pos_);
}

void Evaluator::initAutomaton(size_t i) {
  if( i == 0) {
    for(auto &state: DFA().states) {
      state->visited = 0;
      state->currentL->reset();
    }
    DFA().initState()->currentL->add(Evaluator::memory_manager_.alloc());
  }

  DFA().initState()->visited = i+1;

  current_states_.clear();
  current_states_.push_back(DFA().initState());

  capture_states_.clear();
  if(!DFA().initState()->c.empty())
      capture_states_.push_back(DFA().initState());

  if(early_output_) captureT(i);
  else              captureF(i);
}

bool Evaluator::hasNext() {
  // Decide which next to use.
  static bool (Evaluator::*nexts[])() = {
    &Evaluator::hasNextFF,
    &Evaluator::hasNextFT,
    &Evaluator::hasNextTF,
    &Evaluator::hasNextTT,
  };
  int index = 2 * line_by_line_ +
              1 * early_output_;

  return (this->*nexts[index])();
}

Match Evaluator::next() {
  return enumerator_->next();
}

inline bool
Evaluator::inlinedHasNext(bool early_output, bool line_by_line) {

  #ifndef NDEBUG
  std::cout << "[Eval] hasNext called with args: e_out=" << early_output
            << ", lbl=" << line_by_line << '\n';
  #endif

  if(enumerator_->hasNext())
      return true;

  while (!document_ended_) {

    char a = 0;
    output_nodelist_.reset();

    while(((i_pos_-i_start_) < line_.size() &&  line_by_line_) ||
          (i_pos_ < text_->size()             && !line_by_line_)) { // Main search loop

      if(line_by_line_)   a = line_[i_pos_-i_start_];
      else                text_->get(a);

      #ifndef NDEBUG
      std::cout << "[Eval] Read an \"" << a << "\"\n";
      #endif

      if(early_output_)   readingT(a, i_pos_);
      else                readingF(a, i_pos_);

      current_states_.swap(new_states_);

      if(early_output_)   captureT(i_pos_+1);
      else                captureF(i_pos_+1);

      i_pos_++;

      if(early_output_) {
        if(!output_nodelist_.empty())
          break;
      }
    }

    for(auto &state: current_states_) {
      #ifndef NDEBUG
      std::cout << "[Eval] State " << *state << " was on current_states on outputing process.\n";
      #endif
      if(state->isFinal) {
        #ifndef NDEBUG
        std::cout << "[Eval] Found that dstate " << *state << " is final "
                  << "and it's trying to append its NodeList: "
                  << state->currentL->pprint(rgx_->detManager().varFactory())
                  << '\n';
        #endif
        output_nodelist_.append(state->currentL);
      }
    }
    if(!output_nodelist_.empty()) {
      #ifndef NDEBUG
      std::cout << "[Eval] Passing Output NodeList to Enum: "
                << output_nodelist_.pprint(rgx_->detManager().varFactory())
                << '\n' ;
      #endif
      enumerator_->addNodeList(output_nodelist_);
      memory_manager_.addPossibleGarbage(output_nodelist_.head);
    }

    if(((i_pos_-i_start_) == line_.size()   &&  line_by_line_) ||
       (i_pos_ == text_->size()             && !line_by_line_)) {
      if(line_by_line_) {
        while(!(document_ended_ = !((bool) text_->getline(line_)))) {
          line_ += '\n';
          i_pos_++;
          i_start_ = i_pos_;

          if(!match()) {
            i_pos_ += line_.size() - 1;
            continue;
          }
          else {
            initAutomaton(i_start_);
            break;
          }
        }
      }
      else {
        document_ended_ = true;
      }
    }
  }

  return enumerator_->hasNext();
}

bool Evaluator::match() {
  char a;
  DetState *nextState, *currentState;

  currentState = rawDFA().initState();

  size_t it = 0;

  while( it < line_.size() ) {
    a = (char) line_[it];
    // nextState is reached from currentState by reading the character
    nextState = currentState->nextState(a);

    if(nextState == nullptr) // Then maybe a determinization is needed
      nextState = rgx_->rawDetManager().getNextDetState(currentState, a);

    if (nextState->isSuperFinal)
      return true;

    if (nextState->ss->isNonEmpty)  // Check if not empty set
      currentState = nextState;
    else
      return false;
    it++;
  }

  return currentState->isFinal;
}

inline void Evaluator::capture(size_t i, bool early_output) {
  DetState* nextState;
  Node* newNode;

  for (auto &currentState: capture_states_) {
    currentState->copiedList->head = currentState->currentL->head;
    currentState->copiedList->tail = currentState->currentL->tail;
  }

  for (auto &currentState: capture_states_) {
    for (auto &capture: currentState->c) {

      capture_counter_++;
      nextState = capture->next;

      newNode = memory_manager_.alloc(capture->S, i,
                                       currentState->copiedList->head,
                                       currentState->copiedList->tail);
      // Early output case
      if(early_output && nextState->isSuperFinal)
        output_nodelist_.add(newNode);
      else {
        if (nextState->visited < i+1) {
          nextState->currentL->resetAndAdd(newNode);
          nextState->visited = i+1;

          current_states_.push_back(nextState);
        }
        else {
          nextState->currentL->add(newNode);
        }
      }
    }
  }
}

inline void Evaluator::reading(char a, size_t i, bool early_output) {
  capture_states_.clear();
  new_states_.clear();
  DetState* nextState;
  NodeList* prevList;

  for (auto &currentState: current_states_) {

    reading_counter_++;

#ifdef NOPT_CROSSPROD
    if(currentState->visited == i+2)
      prevList = currentState->oldL;
    else
#endif
      prevList = currentState->currentL;

    // nextState is reached from currentState by reading the character
    nextState = currentState->nextState(a);

    if(nextState == nullptr) { // Then maybe a determinization is needed
      nextState = rgx_->detManager().getNextDetState(currentState, a);
    }

    if(early_output && nextState->isSuperFinal) {  // Early Output check
      output_nodelist_.append(prevList);
    }
    else {
      if (nextState->ss->isNonEmpty) {  // Check if not empty set
        if (nextState->visited <= i+1) { // If not already visited
          nextState->visited = i+2; // Mark as visited

#ifdef NOPT_CROSSPROD
          nextState->oldL->head = nextState->currentL->head;
          nextState->oldL->tail = nextState->currentL->tail;
#endif

          // Pass the list to nextState
          nextState->currentL->head = prevList->head;
          nextState->currentL->tail = prevList->tail;

          this->new_states_.push_back(nextState);

          if (!nextState->c.empty())
            this->capture_states_.push_back(nextState);

        }
        else { // If already visited
          // Append (concat) nextState's currentL with previous list
          nextState->currentL->append(prevList);
        }
      }
      else { // If empty set is reached then consider adding to garbage collection
        prevList->resetRefs();
        Evaluator::memory_manager_.addPossibleGarbage(prevList->head);
      }
    }
  }
}

DetAutomaton& Evaluator::rawDFA() {return rgx_->rawDetManager().DFA();}
DetAutomaton& Evaluator::DFA() {return rgx_->detManager().DFA();}


// Callers of inline versions

bool Evaluator::hasNextFF() {
  return inlinedHasNext(0, 0);
}
bool Evaluator::hasNextFT() {
  return inlinedHasNext(0, 1);
}
bool Evaluator::hasNextTF() {
  return inlinedHasNext(1, 0);
}
bool Evaluator::hasNextTT() {
  return inlinedHasNext(1, 1);
}
void Evaluator::captureT(size_t i) {
  capture(i, 1);
}
void Evaluator::captureF(size_t i) {
  capture(i, 0);
}
void Evaluator::readingT(char a, size_t i) {
  reading(a, i, 1);
}
void Evaluator::readingF(char a, size_t i) {
  reading(a, i, 0);
}

} // end namespace rematch