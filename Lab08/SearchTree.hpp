/*
  Filename   : SearchTree.hpp
  Author     : Gary M. Zoppetti, Jordan Rios, Trey Gretzinger
  Course     : CSCI 362
  Description: Binary search tree class, 
                 a basis for implementing associative ADTs
		 like set and map. 
*/

/************************************************************/
// Macro guard

#ifndef SEARCHTREE_HPP
#define SEARCHTREE_HPP

/************************************************************/
// System includes

#include <iostream>
#include <algorithm>
#include <iterator>
#include <queue>

/************************************************************/
// Local includes

/************************************************************/
// Using declarations

using std::ostream;
using std::queue;

/************************************************************/

template<typename T>
struct Node
{
  using NodePtr = Node*;

  // TODO
  Node (const T& d = T ())
  : data(d), right(nullptr), left(nullptr), parent(nullptr)
  {
    // Initialize data, left, right, and parent in
    //   the member initialization list.
    // left, right, and parent should be set to nullptr.
    // The body of this constructor should be empty.
  }

  // TODO
  Node (const T& d, NodePtr l, NodePtr r, NodePtr p)
  : data(d), right(r), left(l), parent(p)
  {
    // Initialize data, left, right, and parent in
    //   the member initialization list.
    // The body of this constructor should be empty.
  }

  //**

  T        data;
  NodePtr  left;
  NodePtr  right;
  NodePtr  parent;
};

/************************************************************/

// Forward declaration
template <typename T>
class SearchTree;

/************************************************************/

template <typename T>
struct TreeIterator
{
  friend class SearchTree<T>;

  using Self = TreeIterator<T>;
  using NodePtr = Node<T>*;
  using ConstNodePtr = const Node<T>*;

  using difference_type = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;

  using value_type = T;
  using pointer = const T*;
  using reference = const T&;

  TreeIterator ()
    : m_nodePtr ()
  { }

  explicit
  TreeIterator (ConstNodePtr n)
    : m_nodePtr (n)
  { }

  // TODO
  reference
  operator* () const
  {
    // Return the data associated with the referenced node.
    return m_nodePtr->data;
  }

  // Return address of node's data member.
  pointer
  operator-> () const
  {
    return &*this;
  }

  // Pre-increment
  Self&
  operator++ ()
  {
    m_nodePtr = increment (m_nodePtr);
    return *this;
  }

  // Post-increment
  // TODO
  Self
  operator++ (int)
  {
    // Increment iterator so it points to in-order successor.
    // Return appropriate iterator. 
    TreeIterator copy (*this);
    m_nodePtr = increment(m_nodePtr);
    return copy;
  }

  // Pre-decrement
  Self&
  operator-- ()
  {
    m_nodePtr = decrement (m_nodePtr);
    return *this;
  }

  // Post-decrement
  // TODO
  Self
  operator-- (int)
  {
    // Decrement iterator so it points to in-order predecessor.
    // Return appropriate iterator.
    TreeIterator copy (*this);
    m_nodePtr = decrement(m_nodePtr);
    return copy;
     
  }

  bool
  operator== (const Self& i) const
  {
    return m_nodePtr == i.m_nodePtr;
  }

  bool
  operator!= (const Self& i) const
  {
    return m_nodePtr != i.m_nodePtr;
  }

private:
  // TODO
  static ConstNodePtr
  increment (ConstNodePtr n)
  {
    // Return in-order successor of "n".
     if(n->right) 
     {
        n = n->right;
        while(n->left != nullptr) 
        {
          n = n->left;
        }
    } 
    else {
      while(n->parent->right == n && n->parent->parent != n)
      {
          n = n -> parent;
       }
      n = n->parent;
      }
    return n;
  }

  // TODO
  static ConstNodePtr
  decrement (ConstNodePtr n)
  {
    // Return in-order predecessor of "n".
    if(n->left) 
    {
      n = n->left;
      while(n->right != nullptr) 
      {
        n = n->right;
      }
    } 
    else 
    {
      while(n->parent->left == n && n->parent->parent != n)
        {
         n = n -> parent;
        }
      n = n->parent;
    }
    return n;
  }

  // FOR TESTING, otherwise would be PRIVATE
public:

  ConstNodePtr m_nodePtr;
};

/************************************************************/

template <typename T>
class SearchTree
{
  friend class TreeIterator<T>;

public:

  // DO NOT MODIFY type aliases!
  using value_type = T;
  using pointer =  T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  using iterator = TreeIterator<T>;
  using const_iterator = TreeIterator<T>;

  // Header parent points to root of tree or is nullptr
  //   if the tree is empty.
  // Header left points to LARGEST node or is nullptr
  //   if the tree is empty.  
  // Header right points to SMALLEST node or is nullptr
  //   if the tree is empty.
  // size represents the number of elements in the tree.
  SearchTree ()
    : m_header (), m_size (0)
  {
  }

  // Copy constructor
  // TODO
  SearchTree (const SearchTree& t)
  {
    treeCopy(t.m_header.parent);
  }

  ~SearchTree ()
  {
    clear ();
  }

  // Return whether the tree is empty.
  // TODO
  bool
  empty () const
  {
    return m_size == 0;
  }

  // Return the size.
  // TODO
  size_t
  size () const
  {
    return m_size;
  }

  int
  depth () const
  {
    return depth (m_header.parent);
  }
  
  // Return an iterator pointing to the smallest element. 
  // TODO
  iterator
  begin ()
  {
    return iterator (m_header.right);
  }

  // TODO
  const_iterator
  begin () const
  {
    return const_iterator (m_header.right);
  }

  // Return an iterator pointing one beyond the last element,
  //   i.e. the header node. 
  // TODO
  iterator
  end ()
  {
    return iterator (&m_header);
  }

  // TODO
  const_iterator
  end () const
  {
    return const_iterator (&m_header);
  }

  iterator
  find (const T& v) const
  {
    // Call private helper method
    ConstNodePtr n = findHelper (v);
    if (n == nullptr)
    {
      // Wasn't found so return end ()
      n = &m_header;
    }
    return iterator (n);
  }

  std::pair<iterator, bool>
  insert (const T& v)
  {
    NodePtr insertedNode = insert (v, m_header.parent, &m_header);
    bool inserted = insertedNode != nullptr;
    if (inserted)
    {
      // Update header right to point to smallest node
      if (m_header.right == nullptr || v < m_header.right->data)
        m_header.right = insertedNode;
      // Update header left to point to largest node
      if (m_header.left == nullptr || v > m_header.left->data)
        m_header.left = insertedNode;
    }

    return { iterator (insertedNode), inserted };
  }

  size_t
  erase (const T& v)
  {
    // Update header right to point to smallest node
    if (m_header.right != nullptr && v == m_header.right->data)
      m_header.right =
        const_cast<NodePtr> (iterator::increment (m_header.right));
    // Update header left to point to largest node
    else if (m_header.left != nullptr && v == m_header.left->data)
      m_header.left =
        const_cast<NodePtr> (iterator::decrement (m_header.left));
    
    bool erased = erase (v, m_header.parent);
    // If we erased the last value set header left and right to nullptr
    if (erased && empty ())
      m_header.left = m_header.right = nullptr;
    
    return erased ? 1 : 0;
  }

  // Delete all nodes, set header's parent, left, and right links to nullptr,
  //   and set size to 0. Utilizes a private, recursive "clear"
  //   declared below. 
  // TODO
  void
  clear ()
  {
    clear(m_header.parent);
    m_header.parent = nullptr;
    m_header.left = nullptr;
    m_header.right = nullptr;
    m_size = 0;
  }

  void
  printInOrder (ostream& out) const
  {
    printInOrder (out, m_header.parent);
  }

  void
  printLevelOrder (ostream& out) const
  {
    printLevelOrder (out, m_header.parent);
  }

private:

  using Node = struct Node<T>;
  using NodePtr = Node*;
  using ConstNodePtr = const Node*;


  void treeCopy(NodePtr n)
  {
    if(n == nullptr){
      return;
    }
    insert(n->data);
    treeCopy(n->left);
    treeCopy(n->right);
  }

  int
  depth (ConstNodePtr r) const
  {
    if (r == nullptr)
      return -1;
    return std::max (depth (r->left), depth (r->right)) + 1;
  }

  // TODO
  NodePtr
  minimum (NodePtr r) const
  {
    // Return minimum node in tree rooted at "r".
    if(r == nullptr) 
    {
      return nullptr;
    }
    if(r->left == nullptr) 
    {
      return r;
    }
    return minimum(r->left);
  }

  // TODO
  NodePtr
  maximum (NodePtr r) const
  {
    // Return maximum node in tree rooted at "r".
    if(r == nullptr) 
    {
    return nullptr;
    }
    if(r->right == nullptr) 
    {
      return r;
    }
    return maximum(r->right);
  }

  // TODO
  ConstNodePtr
  findHelper (const T& v) const
  {
    // Return a pointer to the node that contains "v".
    NodePtr n = m_header.parent;
    while(n != nullptr){
      if(n->data == v) 
      {
        return n;
      } 
      else if( n->data > v) 
      {
        n = n->left;
      }
      else if(n->data < v) 
      {
        n = n->right;
      }
    }
    return nullptr;
  }

  // TODO
  NodePtr
  insert (const T& v, NodePtr& r, NodePtr parent)
  {
    // Insert "v" into the tree rooted at "r".
    // Use "parent" for recursion and setting the parent of the
    //   node containing "v".

    //Case of an empty tree
    if(r == nullptr){
      r = new Node(v, nullptr, nullptr, parent);
      ++m_size;
      return r;
    }

    //Case of a tree thats not empty
    if(r != nullptr) 
    {
      if(v < r->data) 
      {
        return insert(v,r->left,r);
      } 
      else if(v > r->data)
      {
        return insert(v,r->right,r);
      } 
      else 
      {
        return nullptr;
      }
    }

    return nullptr;
  }

  // TODO
  bool
  erase (const T& v, NodePtr& r)
  {
    // Erase "v" from the tree rooted at "r".
    // Return whether the erase succeeded or not.
    if (r == nullptr)
    {
      return false;
    }
    if (v == r->data)
    {  
      NodePtr temp = r;
      if (r->left == nullptr)
      {
        r = r->right;
      }
      else if (r->right == nullptr)
      {
        r = r->left;
      }
      else
      {
        // node has two children
        temp = minimum(r->right);
        r->data = temp->data;
        return erase(temp->data, r->right);
      }
      if (r != nullptr)
      {
        r->parent = temp->parent;
      }
        delete temp;
        --m_size;
        return true;
    }
    else if (v < r->data)
    {
      return erase(v, r->left);
    }
    else
    {
      return erase(v, r->right);
    }
  }

  // TODO
  void
  clear (NodePtr r)
  {
   // Delete all nodes in the tree rooted at "r".
    if(r) 
    {
      if(r->left != nullptr)
      {
        clear(r->left);
      }
      else if(r->right != nullptr)
      {
        clear(r->right);
      }
      delete r;
    }
  }

  void
  printInOrder (ostream& out, NodePtr r) const
  {
    if (r != nullptr)
    {
      printInOrder (out, r->left);
      out << r->data << " ";
      printInOrder (out, r->right);
    }
  }

  // TODO
  // FIXME: This routine is INCORRECT and is only meant to
  //   show you some techniques you MAY want to employ. 
  // Rewrite this method to output elements in the form required
  //   by the operator<< below. 
  void
  printLevelOrder (ostream& out, NodePtr r) const
  {
   if (r == nullptr)
    {
      return;
    }
    if (m_size == 1)
    {
      out << r->data << " ";
    }
    else
    {
      queue<NodePtr> q;
      q.push(r);
      int level = 0;
      int rowNodes = 1;
      while (!q.empty() && level <= depth(r))
      {
        for (int i = 0; i < rowNodes; ++i)
        {
          NodePtr curr = q.front();
          q.pop();
          if (curr != nullptr)
          {
            out << curr->data << " ";
            q.push(curr->left);
            q.push(curr->right);
          }
          else
          {
            out << "- ";
            q.push(nullptr);
            q.push(nullptr);
          }
        }
        if (level < depth(r))
        {
        out << "| ";
        }
        ++level;
        rowNodes *= 2;
      }
    }
  }

private:

  Node   m_header;
  size_t m_size;
};

/************************************************************/

// Output tree as [ e1 e2 e3 ... en ]
//   with a '|' to indicate the end of a level,
//   and a '-' to indicate a missing node.
// E.g., the tree
//       4
//    2     7
//         6
// should be printed EXACTLY like so: [ 4 | 2 7 | - - 6 - ]
// ONLY print the levels that exist, and ensure each level contains
//   2^k entries (a T object or "-"), where "k" is the level number. 
template<typename T>
ostream&
operator<< (ostream& out, const SearchTree<T>& tree)
{
  out << "[ ";
  // For the version you submit, ensure you are using "printLevelOrder"!
  // You may find "printInOrder" useful for early testing, since it's
  //   been written for you.
  //tree.printInOrder (out);
  tree.printLevelOrder (out);
  out << "]";

  return out;
}

/************************************************************/

#endif

/************************************************************/
