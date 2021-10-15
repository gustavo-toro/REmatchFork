#ifndef STRUCTS__HOW__HOW_HPP
#define STRUCTS__HOW__HOW_HPP

#include <string>

namespace rematch {
namespace ranked {

template <typename T, typename G>
class HeapOfWords {
 public:
  virtual HeapOfWords<T,G>* add(T obj, G val) const = 0;

  virtual HeapOfWords<T,G>* extend_by(T obj) const = 0;

  virtual std::list<T> find_min() const = 0;

  virtual HeapOfWords<T,G>* delete_min() const = 0;

  virtual HeapOfWords<T,G>* meld_with(HeapOfWords<T, G>* h) const = 0;

  virtual HeapOfWords<T,G>* increase_by(G val) const = 0;

  virtual bool empty() const = 0;

}; // end class HeapOfWords

} // end namespace ranked
} // end namespace rematch

#endif // STRUCTS__HOW__HOW_HPP