#ifndef DETSTATE_HPP
#define DETSTATE_HPP

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <bitset>

#include "bitsetwrapper.hpp"
#include "structs/dag/fastnodelist.hpp"
#include "det/setstate.hpp"
#include "captures.hpp"

namespace rematch {

class Transition;

class DetState {
  private:
    static unsigned int ID; // Static var to make sequential id's
  public:
    /* Unique ID*/
    unsigned int id;                              // id

    // Transitions to other states
    std::array<std::unique_ptr<Transition>, 128> transitions_;

    // Label used for debugging
    std::string label;

    DetState* drop_super_finals_ = nullptr;

    int64_t visited;  // Mark the reading iteration for which the State is prepared

    internal::FastNodeList* currentL;
    internal::FastNodeList* copiedList;

    SetState* ss;

    bool isFinal, isSuperFinal, mark, isOnlyInit, hasCapture;

    DetState();
    DetState(SetState* ss);

    Transition* next_transition(char a);

    DetState* drop_super_finals() { return drop_super_finals_;}
    void set_drop_super_finals(DetState* s) {drop_super_finals_ = s;}

    void add_capture(char a, std::bitset<32> S, DetState* state);
    void add_direct(char a, DetState* state);
    void add_empty(char a, DetState* state);

    // Remove SuperFinals states from the detState;
    bool remove_superfinals();

    bool empty() const { return ss->subset.empty(); }



    DetState* nextState(BitsetWrapper charBitset);
    DetState* nextState(char a);
    internal::NodeList* getPreviousList(int i);
    void setFinal(bool b);
    void setSubset(SetState* newss);
    std::string pprint();
    friend std::ostream & operator<<(std::ostream &os, DetState const &bs);
};


std::ostream & operator<<(std::ostream &os, DetState const &q);

} // end namespace rematch

#endif
