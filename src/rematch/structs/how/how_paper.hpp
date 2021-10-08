#ifndef SRC_REMATCH_STRUCTS_HOW_HOW_PAPER_HPP
#define SRC_REMATCH_STRUCTS_HOW_HOW_PAPER_HPP

#include <memory>
#include <list>

#include "structs/how/how.hpp"
#include "structs/how/iheap.hpp"
#include "structs/how/binomial_heap.hpp"

namespace rematch {
namespace ranked {

template<typename T, typename G>
class HoWPaper : public HeapOfWords<T,G> {
 public:

  using HoW = HoWPaper<T,G>;

  struct HoWNode {
    T a;
    const HoW *h;
  };

  HoWPaper() : Q_(new BinomialHeap<HoWNode,G>()) {}

  virtual HoW* add(T obj, G val) const {
    return new HoW(Q_->add({obj, new HoW()}, val));
  }

  virtual HoW* extend_by(T obj) const {
    if(Q_->empty())
      return new HoW();
    BinomialHeap<HoWNode, G>* empty_heap = new BinomialHeap<HoWNode, G>();
    return new HoW(empty_heap->add({obj, this}, Q_->min_prio()));
  }

  virtual std::list<T> find_min() const {
    std::list<T> ret;
    auto &tmp = Q_->find_min();
    T& a = tmp.a;
    auto* h_prim = tmp.h;
    ret.push_back(a);
    if(!h_prim->Q_->empty()) {
      // Append list to the end
      std::list<T> rec_ret = h_prim->find_min();
      ret.splice(ret.end(), rec_ret);
    }
    return ret;
  };

  virtual G min_prio() const { return Q_->min_prio(); }

  virtual HoW* delete_min() const {
    if (Q_->empty()) {
      return new HoW();
    }
    auto &tmp = Q_->find_min();
    T& a = tmp.a;
    auto *h_r = tmp.h;
    auto R = h_r->Q_;
    auto Q_p = Q_->delete_min();
    HoW *h_r_prim = h_r->delete_min();
    auto R_p = h_r_prim->Q_;
    if (R_p->empty()) {
      return new HoW(Q_p);
    }
    // TODO: Documentar esto
    G delta = R_p->min_prio() - R->min_prio();
    G g = Q_->min_prio() + delta;
    return new HoW(Q_p->add({a, h_r_prim}, g));
  };

  virtual HoW* meld_with(HeapOfWords<T,G>* h) const {
    HoW* h_derived = static_cast<HoW*>(h);
    return new HoW(Q_->meld_with(h_derived->Q_));
  };

  virtual HoW* increase_by(G val) const {
    return new HoW(Q_->increase_by(val));
  };

  virtual bool empty() const { return Q_->empty(); }


 private:
  // HoWPaper(IncrementalHeap<HoWNode, G>* Q): Q_(Q) {}
  HoWPaper(BinomialHeap<HoWNode, G>* Q): Q_(Q) {}

  // IncrementalHeap<HoWNode, G>* Q_;
  BinomialHeap<HoWNode, G>* Q_;
}; // end class HoWPaper

} // end namespace ranked
} // end namespace rematch

#endif // SRC_REMATCH_STRUCTS_HOW_HOW_PAPER_HPP