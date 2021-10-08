#ifndef STRUCTS__HOW__HEAP_HPP
#define STRUCTS__HOW__HEAP_HPP

namespace rematch {
namespace ranked {

template<typename T, typename G>
class Heap {

 public:
  virtual T& find_min() const = 0;

  virtual Heap<T,G>* delete_min() = 0;

  virtual Heap<T,G>* add(T obj, G value) = 0;

  virtual Heap<T,G>* meld_with(Heap<T,G> *h) = 0;

  virtual bool empty() const = 0;

  virtual const G& min_prio() const = 0;

}; // end class Heap<T,G>

} // end namespace ranked
} // end namespace rematch

#endif // STRUCTS__HOW__HEAP_HPP