#ifndef STRUCTS__CAPTURE_PLACE_HPP
#define STRUCTS__CAPTURE_PLACE_HPP

#include <bitset>

namespace rematch {

using capture_t = std::bitset<32>;

struct CapturePlace {
  capture_t S;
  long i;
};

// Set the Bottom capture
const CapturePlace kBottomCapture{0,-1} ;

} // end namespace rematch

#endif // STRUCTS__CAPTURE_PLACE_HPP