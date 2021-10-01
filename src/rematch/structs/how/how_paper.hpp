#ifndef STRUCTS__HOW__HOW_PAPER_HPP
#define STRUCTS__HOW__HOW_PAPER_HPP

#include <memory>

#include "structs/how/how.hpp"
#include "structs/how/iheap.hpp"

namespace rematch {
namespace ranked {


template<typename T, typename K>
class HOWPaper : public HeapOfWords<T,K> {
 public:
  using hpair_t = std::pair<T, HOWPaper*>;

  HOWPaper() = default;

  virtual HOWPaper<T,K>& add(T& obj, K val) {
    Q_ = Q_->add(std::make_pair(obj, HOWPaper<T,K>()), val);
    return *this;
  }

  virtual HOWPaper<T,K>& extend_by(T& obj) {
    if(Q_->empty())
      return *this;
    IncHeap<hpair_t, K>* empty_heap = new IncHeap<hpair_t, K>();
    Q_ = empty_heap->add(std::make_pair(obj, this), Q_->min_prio());
  }

  virtual void find_min() = 0;

  virtual void delete_min() = 0;

  virtual void meld_with(HeapOfWords<T, K>& h) = 0;

  virtual void increase_by(K val) = 0;


 private:
  std::unique_ptr<IncHeap<hpair_t, K>> Q_;
}; // end class HOWPaper

} // end namespace ranked
} // end namespace rematch

#endif // STRUCTS__HOW__HOW_PAPER_HPP