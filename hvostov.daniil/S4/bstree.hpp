#include <cstddef>
#include <memory>
#include <utility>
#include <stdexcept>
#include <functional>

namespace hvostov {

  namespace detail {
    template < class Key, class Value >
    struct Node {
      std::pair< const Key, Value > data;
      Node< Key, Value >* parent;
      Node< Key, Value >* left;
      Node< Key, Value >* right;
      size_t height = 0;

      Node() = default;
      Node(const Key& k, const Value& v, Node* p);
      Node(const Key& k, Value&& v, Node* p);
      ~Node() = default;
    };
  }

  template < class Key, class Value >
  class BSTIterator;

  template < class Key, class Value >
  class BSTConstIterator;

  template < class Key, class Value, class Compare = std::less< Key > >
  class BSTree {
  public:
    using node_t = detail::Node< Key, Value >;
    using iterator = BSTIterator< Key, Value >;
    using const_iterator = BSTConstIterator< Key, Value >;

    BSTree();
    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;
    BSTree& operator=(const BSTree& other);
    BSTree& operator=(BSTree&& other) noexcept;
    ~BSTree();

    void push(const Key& k, const Value& v);
    void push(const Key& k, Value&& v);
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    Value drop(const Key& k);

    const_iterator rotateLeft(const_iterator it);
    const_iterator rotateRight(const_iterator it);
    const_iterator rotateLargeRight(const_iterator it);
    const_iterator rotateLargeLeft(const_iterator it);

    size_t height(const_iterator it) const;
    size_t height() const;

    void swap(BSTree& other) noexcept;
    void clear() noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

  private:
    node_t* root_;
    size_t size_;
    Compare comp_;

    node_t* copy(node_t* other, node_t* parent);
    void clearSubtree(node_t* node) noexcept;
    size_t calcHeight(node_t* node) const;
    void updateHeightUpwards(node_t* node);
    node_t* findNode(const Key& k) const;
    node_t* minimum(node_t* node) const;
    node_t* maximum(node_t* node) const;
  };

  template < class Key, class Value >
  class BSTIterator {
  public:
    BSTIterator() = default;
    BSTIterator(const BSTIterator& other) = default;
    BSTIterator(BSTIterator&& other) noexcept = default;
    BSTIterator& operator=(const BSTIterator& other) = default;
    BSTIterator& operator=(BSTIterator&& other) noexcept = default;
    ~BSTIterator() = default;

    detail::Node< Key, Value >& operator*();
    detail::Node< Key, Value >* operator->();

    BSTIterator& operator++();
    BSTIterator operator++(int);
    BSTIterator& operator--();
    BSTIterator operator--(int);

    bool operator==(const BSTIterator& other) const;
    bool operator!=(const BSTIterator& other) const;

  private:
    template < class, class, class >
    friend class BSTree;
    detail::Node< Key, Value >* curr_;
    BSTIterator(detail::Node< Key, Value >* node);
  };

  template < class Key, class Value >
  class BSTConstIterator {
  public:
    BSTConstIterator() = default;
    BSTConstIterator(const BSTConstIterator& other) = default;
    BSTConstIterator(BSTConstIterator&& other) noexcept = default;
    BSTConstIterator& operator=(const BSTConstIterator& other) = default;
    BSTConstIterator& operator=(BSTConstIterator&& other) noexcept = default;
    ~BSTConstIterator() = default;

    const detail::Node< Key, Value >& operator*() const;
    const detail::Node< Key, Value >* operator->() const;

    BSTConstIterator& operator++();
    BSTConstIterator operator++(int);
    BSTConstIterator& operator--();
    BSTConstIterator operator--(int);

    bool operator==(const BSTConstIterator& other) const;
    bool operator!=(const BSTConstIterator& other) const;

  private:
    template < class, class, class >
    friend class BSTree;
    detail::Node< Key, Value >* curr_;
    BSTConstIterator(detail::Node< Key, Value >* node);
  };

}

template < class Key, class Value >
hvostov::detail::Node< Key, Value >::Node(const Key& k, const Value& v, Node* p) :
  data(k, v),
  parent(p),
  left(nullptr),
  right(nullptr),
  height(0)
{
}

template < class Key, class Value >
hvostov::detail::Node< Key, Value >::Node(const Key& k, Value&& v, Node* p) :
  data(k, std::move(v)),
  parent(p),
  left(nullptr),
  right(nullptr),
  height(0)
{
}

template < class Key, class Value, class Compare >
hvostov::BSTree< Key, Value, Compare >::BSTree() :
  root_(nullptr),
  size_(0),
  comp_(Compare())
{
}

template < class Key, class Value, class Compare >
hvostov::BSTree< Key, Value, Compare >::BSTree(const BSTree& other) :
  root_(nullptr),
  size_(other.size_),
  comp_(other.comp_)
{
  root_ = copy(other.root_, nullptr);
}

template < class Key, class Value, class Compare >
hvostov::BSTree< Key, Value, Compare >::BSTree(BSTree&& other) noexcept :
  root_(std::exchange(other.root_, nullptr)),
  size_(std::exchange(other.size_, 0)),
  comp_(std::move(other.comp_))
{
}

template < class Key, class Value, class Compare >
hvostov::BSTree< Key, Value, Compare >& hvostov::BSTree< Key, Value, Compare >::operator=(const BSTree& other)
{
  if (this != std::addressof(other)) {
    BSTree temp(other);
    swap(temp);
  }
  return *this;
}

template < class Key, class Value, class Compare >
hvostov::BSTree< Key, Value, Compare >& hvostov::BSTree< Key, Value, Compare >::operator=(BSTree&& other) noexcept
{
  if (this != std::addressof(other)) {
    clear();
    root_ = std::exchange(other.root_, nullptr);
    size_ = std::exchange(other.size_, 0);
    comp_ = std::move(other.comp_);
  }
  return *this;
}

template < class Key, class Value, class Compare >
hvostov::BSTree< Key, Value, Compare >::~BSTree()
{
  clear();
}

template < class Key, class Value, class Compare >
typename hvostov::BSTree< Key, Value, Compare >::node_t* hvostov::BSTree< Key, Value, Compare >::copy(node_t* other,
                                                                                                      node_t* parent)
{
  if (!other) {
    return nullptr;
  }
  node_t* new_node = new node_t(other->data.first, other->data.second, parent);
  new_node->height = other->height;
  new_node->left = copy(other->left, new_node);
  new_node->right = copy(other->right, new_node);
  return new_node;
}
