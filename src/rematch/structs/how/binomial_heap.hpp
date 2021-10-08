#ifndef STRUCTS__HOW__BINOMIAL_HEAP_HPP
#define STRUCTS__HOW__BINOMIAL_HEAP_HPP

#include <list>

#include "structs/how/heap.hpp"

namespace rematch {
namespace ranked {

template<typename T, typename G>
class BinomialHeap : public Heap<T,G> {
 public:
  using bHeap = BinomialHeap<T,G>;

  BinomialHeap() = default;

  virtual T& find_min() const {
    return find_min_node()->data_;
  }

  virtual bHeap* delete_min() const {
    Node* min_node = find_min_node();

    Node* new_head = min_node->child_->reverse_list()

    // Alloc a new empty heap
    BHeap* H_prim = new BHeap();

    H_prim->set_head(new_head);

    return meld_with(H_prim);
  }

  virtual void add(const T& obj, const G& value) {
    Node* new_node = new Node(obj, value);
    BinomialHeap tmp;
    tmp.tree_list_.push_back(new_node);
    meld_with(tmp);
  }

  virtual void meld_with(BinomialHeap<T,G> &h) {
    merge(h);
    adjust();
  }

  virtual void empty() const {
    return tree_list_.empty();
  }

  virtual const G& min_prio() const {
    return find_min_node()->key_;
  };

 private:
  class Node {
   public:
    Node(T &data, G& key)
        : data_(data),
          key_(key),
          child_(nullptr),
          sibling_(nullptr),
          parent_(nullptr),
          order_(0) {}

    static Node* link(Node* p, Node* q) {
      if(p->key_ > q->key_)
        std::swap(p, q); // Make sure p is smaller

      q->parent_ = p;
      q->sibling_ = p->child_
      p->child_ = q;
      ++p->order_;
      return p;
    }

    // Reverses the siblings list
    Node* reverse_list() {
      
    }

   private:
    T &data_;
    G &key_;

    Node* child_; // Left-most child
    Node* sibling_; // Right sibiling
    Node* parent_;

    int order_;
  }; // end class Node

  Node* merge(bHeap *h) {
    Node *it = head_, *ot = h.head_;
    Node *nhead = (it->order <= ot->order)? it : ot;
    while(it != nullptr && ot != nullptr) {
      if(it->order_ <= ot->order_) {
        new_list_.push_back(it);
        ++it;
      } else {
        new_list_.push_back(ot);
        ++ot;
      }
    }

    while(it != tree_list.end()) {
      new_list_.push_back(*it); ++it;
    }

    while(it != h.tree_list.end()) {
      new_list_.push_back(*ot); ++ot;
    }

    tree_list_ = std::move(new_list_);
  }

  void adjust() {
    if (tree_list_.size() <= 1) return;
    std::list<Node*> new_tree_list;
    std::list<Node*> it1, it2, it3;
    it1 = it2 = it3 = tree_list_.begin();

    if(tree_list_.size() == 2) {
      it2 = it1;
      ++it2;
      it3 = tree_list_.end();
    } else {
      ++it2;
      it3 = it2;
      ++it3;
    }

    while(it1 != tree_list_.end()) {
      if(it2 == tree_list_.end())
        ++it1;
      else if((*it1)->order_ < (*it2)->order_) {
        ++it1; ++it2;
        if(it3 == tree_list_.end())
          ++it3;
      } else if(  it3 != tree_list_.end() &&
                (*it1)->order_ == (*it2)->order_ &&
                (*it2)->order_ == (*it3)->order_) {
        ++it1; ++it2; ++it3;
      } else if( (*it1)->order_  == (*it2)->order_ ) {
        *it1 = merge_trees(*it1, *it2);
        it2 = tree_list_.erase(it2);
        if(it3 != tree_list_.end())
          ++it3;
      }
    }
  }

  Node* find_min_node() const {
    if(empty()) return nullptr;
    Node* tmp = head_;
    Node* current = head_->next_;
    while(current != nullptr) {
      if(node->key_ < tmp_.key_)
        tmp = current;
    }
    return tmp;
  }

  void set_head(Node* h) { head_ = h; }

  Node* head_ = nullptr; // First setted to nullptr

}; // end class BinomialHeap


} // end namespace ranked

} // end namespace rematch

#endif // STRUCTS__HOW__BINOMIAL_HEAP_HPP