#ifndef STRUCTS__HOW__HOW_HPP
#define STRUCTS__HOW__HOW_HPP

namespace rematch {
namespace ranked {

template <typename T, typename K>
class HeapOfWords {

 public:
  virtual HeapOfWords<T,K>& add(T& obj, K val) = 0;

  virtual HeapOfWords<T,K>& extend_by(T& obj) = 0;

  virtual const T& find_min() = 0;

  virtual HeapOfWords<T,K>& delete_min() = 0;

  virtual HeapOfWords<T,K>& meld_with(HeapOfWords<T, K>& h) = 0;

  virtual HeapOfWords<T,K>& increase_by(K val) = 0;

}; // end class HeapOfWords

} // end namespace ranked
} // end namespace rematch

#endif // STRUCTS__HOW__HOW_HPP