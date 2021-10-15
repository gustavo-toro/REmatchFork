#ifndef STRUCTS__HOW__IHEAP_HPP
#define STRUCTS__HOW__IHEAP_HPP

#include <memory>

#include "structs/how/heap.hpp"

namespace rematch {
namespace ranked {

template<typename T, typename G>
class IncrementalHeap {
 public:
  using iHeap = IncrementalHeap<T,G>;
  virtual T& find_min() const = 0;

  virtual iHeap* delete_min() const = 0;

  virtual iHeap* add(T obj, G value) const = 0;

  virtual iHeap* increase_by(G value) const = 0;

  virtual iHeap* meld_with(iHeap *h) const = 0;

  virtual bool empty() const = 0;

  virtual const G& min_prio() const = 0;
}; // class IncHeap

} // end namespace ranked
} // end namespace rematch

#endif // STRUCTS__HOW__IHEAP_HPP