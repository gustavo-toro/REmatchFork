#ifndef STRUCTS__HOW__IHEAP_HPP
#define STRUCTS__HOW__IHEAP_HPP

#include <memory>

#include "structs/how/heap.hpp"

namespace rematch {
namespace ranked {

template<typename T, typename G>
class IncHeap {
 public:
  T& find_min() const {
    return heap_->find_min();
  };

  void delete_min() {
    return heap_->delete_min();
  };

  void add(const T& obj, const G& value) {
    return heap_->add(obj, value);
  }

  void increase_by(const G& value) {
    return heap_->increase_by(value);
  }

  void meld_with(IncHeap<T,G> &h) {
    heap_->meld_with(h.heap_);
  }

  bool empty() const {
    return heap_->empty();
  }

  const G& min_prio() const {
    return heap_->min_prio();
  }

  void increase_by();
 private:
  std::unique_ptr<Heap<T,G>> heap_;

}; // class IncHeap

} // end namespace ranked
} // end namespace rematch

#endif // STRUCTS__HOW__IHEAP_HPP