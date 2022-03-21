#ifndef SRC_REMATCH_STRUCTS_HOW_BINOMIAL_HEAP_HPP
#define SRC_REMATCH_STRUCTS_HOW_BINOMIAL_HEAP_HPP

#include <list>

#include "structs/how/iheap.hpp"

namespace rematch {
namespace ranked {

template<typename T, typename G>
class BinomialHeap : public IncrementalHeap<T,G> {
 public:
  using BinHeap = BinomialHeap<T,G>;

  BinomialHeap() = default;

  virtual T& find_min() const {
    return find_min_node()->data_;
  }

  virtual BinHeap* delete_min() const {
    Node* min_node = find_min_node();

    BinHeap* H1 = copy_roots_except(min_node);
    BinHeap* H2 = copy_reverse_siblings(min_node);

    return H1->meld_with(H2);
  }

  virtual BinHeap* add(T obj, G value) const {
    BinHeap* tmp = new BinHeap(new Node(obj, value), delta_0_);
    return meld_with(tmp);
  }

  virtual BinHeap* increase_by(G value) const {
    return new BinHeap(head_, delta_0_ + value);
  }

  virtual BinHeap* meld_with(IncrementalHeap<T,G> *h) const {
    BinHeap* hdev = static_cast<BinHeap*>(h);
    BinHeap* H1_down = copy_roots();
    BinHeap* H2_down = hdev->copy_roots();

    H1_down->head_ = H1_down->merge(H2_down);

    if(H1_down->empty()) return H1_down;

    Node* prev_x = nullptr;
    Node* x = H1_down->head_;
    Node* next_x = x->next();

    while(next_x != nullptr) {
      if( ( x->degree_ != next_x->degree_ ) ||
          ( next_x->next() != nullptr && next_x->next()->degree_ == x->degree_ ) ) {
        prev_x = x;
        x = next_x;
      } else if( x->key_ <= next_x->key_ ) {
        x->set_sibling(next_x->next());
        Node::link_deltas(x, next_x);
      } else {
        if( prev_x == nullptr ) // At start
          H1_down->head_ = next_x;
        else
          prev_x->set_sibling(next_x);
        Node::link_deltas(next_x, x);
        x = next_x;
      }
      next_x = x->next();
    }

    return H1_down;
  }


  virtual bool empty() const {
    return head_ == nullptr;
  }

  virtual const G& min_prio() const {
    return find_min_node()->key_;
  };

 private:

  class Node {
   friend BinomialHeap<T,G>;
   public:

    Node(T &data, G& key)
        : data_(data),
          key_(key),
          child_(nullptr),
          sibling_(nullptr),
          parent_(nullptr),
          degree_(0) {}


    static Node* link(Node* n1, Node* n2) {
      if(n1->key_ > n2->key_)
        std::swap(n1, n2); // Make sure n1 is smaller

      n2->parent_ = n1;
      n2->sibling_ = n1->child_;
      n1->child_ = n2;
      ++n1->degree_;
      return n1;
    }

    // Binomial link of two binomial trees. With the correction of the deltas.
    static void link_deltas(Node* n1, Node* n2) {
      if(n1->key_ > n2->key_)
        std::swap(n1, n2); // Make sure n1 is smaller

      // NOTE: No need to make a copy of the nodes
      // Node* n1_prim = new Node(n1);
      // Node* n2_prim = new Node(n2);
      n2->sibling_ = n1->child_;
      n1->child_ = n2;
      n2->parent_ = n1;
      n2->key_ = n2->key_ - n1->key_;
      ++n1->degree_;
    }

    Node* next() const { return sibling_; }
    void set_sibling(Node* s) { sibling_ = s; }

    Node* first() const { return child_; }

    Node* parent() const { return parent_; }
    void set_parent(Node* p) { parent_ = p; }

    void set_key(G nk) { key_ = nk; }
    G key() const { return key_; }

   private:
    T data_;
    G key_;

    Node* child_; // Left-most child
    Node* sibling_; // Right sibiling
    Node* parent_;

    int degree_;
  }; // end class BinomialHeap::Node

  BinomialHeap(Node* h, G delta): head_(h), delta_0_(delta) {}

  // Performs a copy of all the roots of the heap. Returns a new Heap that has
  // the new roots.
  BinHeap* copy_roots() const {
    if(head_ == nullptr)
      return new BinHeap(head_, 0);
    Node* new_node = new Node(*head_);
    new_node->set_key(delta_0_ + new_node->key());
    Node *head, *tail;
    head = tail = new_node;
    for(Node* it = head_->sibling_; it != nullptr; it = it->sibling_) {
      new_node = new Node(*it);
      new_node->set_key(delta_0_ + new_node->key());
      tail->set_sibling(new_node);
      tail = new_node;
    };

    return new BinHeap(head, 0);
  };

  // Copies the whole root list, but without a skip node (usually the min node)
  // Returns a new BinomialHeap with the newly allocated nodes as its roots.
  BinHeap* copy_roots_except(Node* skip_node) const {

    // No skip_node -> heap is empty
    if(skip_node == nullptr)
      return new BinHeap(*this);

    // Pointers to new allocated list
    Node* new_tail = nullptr;
    Node* new_head = nullptr;
    Node* new_node;

    // Copy up until the skip_node
    for(Node* it = head_; it != skip_node; it = it->next()) {
      new_node = new Node(*it);
      new_node->set_sibling(nullptr);
      if(new_tail != nullptr)
        new_tail->set_sibling(new_node);
      else
        new_head = new_node;
      new_tail = new_node;
    }

    // Copy from the skip_node to the rest of the list
    for(Node* it = skip_node->next(); it != nullptr; it = it->next()) {
      new_node = new Node(*it);
      if(new_tail != nullptr)
        new_tail->set_sibling(new_node);
      else
        new_head = new_node;
      new_tail = new_node;
    }

    return new BinHeap(new_head, delta_0_);
  }

  // Copies a reversed list of the children nodes of a parent node.
  // Returns a new BinomialHeap with the newly allocated nodes as its roots.
  BinHeap* copy_reverse_siblings(Node* parent_node) const {
    Node *new_prev = nullptr, *new_node;
    if(parent_node->child_ != nullptr) {
      new_prev = new Node(*parent_node->child_);
      new_prev->set_parent(nullptr);
      new_prev->set_sibling(nullptr);

      for(Node* it = parent_node->child_->sibling_; it != nullptr ; it = it->sibling_) {
        new_node = new Node(*it);
        new_node->set_sibling(new_prev);
        new_node->set_parent(nullptr);
        new_prev = new_node;
      }
    }
    return new BinHeap(new_prev, delta_0_ + parent_node->key_);
  }

  // Merge the two root lists of this and another BinomiaHeap h. Does it inplace
  // of the original (so not in a fully persistant way). Returns the new head of
  // the roots.
  Node* merge(BinHeap *h) {
    Node *it = head_, *ot = h->head_;

    // Limit cases
    if(ot == nullptr) return it;
    if(it == nullptr) return ot;

    Node *nhead, *ntail;

    if (it->degree_ <= ot->degree_) {
      nhead = it;
      it = it->next();
    } else {
      nhead = ot;
      ot = ot->next();
    }

    ntail = nhead;

    while(it != nullptr && ot != nullptr) {
      if(it->degree_ <= ot->degree_) {
        ntail->set_sibling(it);
        ntail = it;
        it = it->next();
      } else {
        ntail->set_sibling(ot);
        ntail = ot;
        ot = ot->next();
      }
    }

    while(it != nullptr) {
      ntail->set_sibling(it);
      ntail = it;
      it = it->next();
    }

    while(ot != nullptr) {
      ntail->set_sibling(ot);
      ntail = ot;
      ot = ot->next();
    }

    return nhead;
  }

  Node* find_min_node() const {
    if(empty()) return nullptr;
    Node* tmp = head_;
    Node* current = head_->next();
    while(current != nullptr) {
      if(current->key_ < tmp->key_)
        tmp = current;
      current = current->next();
    }
    return tmp;
  }

  void set_head(Node* h) { head_ = h; }

  Node* head_ = nullptr; // First setted to nullptr
  G delta_0_;

  union garbage_collection {
    uint nreferences;
    BinomialHeap<T,G>* next_free;
  };

}; // end class BinomialHeap


} // end namespace ranked

} // end namespace rematch

#endif // SRC_REMATCH_STRUCTS_HOW_BINOMIAL_HEAP_HPP
