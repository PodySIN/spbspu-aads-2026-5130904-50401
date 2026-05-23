#include <cstddef>
#include <utility>

namespace hvostov {

  namespace detail {
    template < class Key, class Value >
    struct Node {
      std::pair< const Key, Value > node;
      Node< Key, Value >*parent, *left, *right;
      Node() = default;
      Node(const Key& k, const Value& v, Node* p);
      ~Node() = default;
    };
  }

  template < class Key, class Value >
  class BSTIterator;

  template < class Key, class Value >
  class BSTConstIterator;

  template < class Key, class Value, class Compare >
  class BSTree {
  public:
    BSTree();
    BSTree(const BSTree& other);
    BSTree(BSTree&& other) noexcept;
    BSTree& operator=(const BSTree& other);
    BSTree& operator=(BSTree&& other) noexcept;
    ~BSTree();

    void push(const Key& k, const Value& v);
    void push(const Key& k, Value&& v);
    Value get(const Key& k) const;
    Value drop(const Key& k);
    using const_iterator = BSTConstIterator< Key, Value >;
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

    using iterator = BSTIterator< Key, Value >;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

  private:
    detail::Node< Key, Value >* root_;
    size_t size_;
    Compare comp_;
  };

  template < class Key, class Value >
  class BSTIterator {
  public:
    BSTIterator();
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
    BSTConstIterator();
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
