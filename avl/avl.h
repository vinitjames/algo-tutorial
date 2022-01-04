#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include "../bst/bst.h"


template <class T, typename metadata> class AVL : public BST<T, metadata>{
public:
  AVL(){};
  ~AVL();
  

private:
  
 
};

template <class T> inline BST<T>::~BST() {
  if (_root != nullptr) {
    _bfTraversal([](Node<T> *node) {
      if (node != nullptr)
        delete node;
    });
  }
}

template <class T>
inline void BST<T>::forEach(std::function<void(Node<T> *)> for_each) {
  _bfTraversal(for_each);
}
template <class T>
inline void BST<T>::_bfTraversal(std::function<void(Node<T> *)> for_each) {
  if (_root == nullptr)
    return;
  std::queue<Node<T> *> nodes;
  nodes.push(_root);
  while (!nodes.empty()) {
    Node<T> *currNode = nodes.front();
    nodes.pop();
    if (currNode->l_child() != nullptr)
      nodes.push(currNode->l_child());
    if (currNode->r_child() != nullptr)
      nodes.push(currNode->r_child());
    for_each(currNode);
  }
}

template <class T> inline void BST<T>::insert(const T &value) {
  Node<T> *node = new Node<T>();
  node->value(value);
  Node<T> **currRoot = &_root;
  while (*currRoot != nullptr) {
    node->parent(*currRoot);
    if (node->value() < (*currRoot)->value())
      currRoot = (*currRoot)->l_child_ptr();
    else
      currRoot = (*currRoot)->r_child_ptr();
  }
  *currRoot = node;
}

template <class T> inline Node<T> *BST<T>::max() {
  if (_root == nullptr)
    return nullptr;
  return _max(_root);
}

template <class T> inline Node<T> *BST<T>::_max(Node<T> *root) {
  Node<T> *currRoot = root;
  while (currRoot->r_child() != nullptr)
    currRoot = currRoot->r_child();
  return currRoot;
}

template <class T> inline Node<T> *BST<T>::min() {
  if (_root == nullptr)
    return nullptr;
  return _min(_root);
}

template <class T> inline Node<T> *BST<T>::_min(Node<T> *root) {
  Node<T> *currRoot = root;
  while (currRoot->l_child() != nullptr)
    currRoot = currRoot->l_child();
  return currRoot;
}

template <class T> inline void BST<T>::removeNode(const T &value) {
  Node<T> *node = search(value);
  if (node == nullptr) {
    std::cout << "node not found " << std::endl;
    return;
  }
  std::cout << "found node with value " << node->value() << std::endl;
  if ((node->l_child() == nullptr) && (node->r_child() == nullptr))
    _delLeafNode(node);
  else if ((node->l_child() == nullptr) || (node->r_child() == nullptr))
    _delOneChildNode(node);
  else
    _delTwoChildNode(node);
}

template <class T> inline void BST<T>::_delLeafNode(Node<T> *node) {
  if (node->value() < node->parent()->value())
    node->parent()->l_child(nullptr);
  else
    node->parent()->r_child(nullptr);
  delete node;
}

template <class T> inline void BST<T>::_delOneChildNode(Node<T> *node) {
  Node<T> *childNode =
      node->r_child() != nullptr ? node->r_child() : node->l_child();
  childNode->parent(node->parent());
  if (node->parent()->value() < node->value())
    node->parent()->r_child(childNode);
  else
    node->parent()->l_child(childNode);
  delete node;
}

template <class T> inline void BST<T>::_delTwoChildNode(Node<T> *node) {

  Node<T> *inorderSucc = _min(node->r_child());
  if (inorderSucc->parent() == node)
    inorderSucc->parent()->r_child(inorderSucc->r_child());
  else
    inorderSucc->parent()->l_child(inorderSucc->r_child());
  /*inorderSucc->parent(node->parent());
  inorderSucc->l_child(node->l_child());
  inorderSucc->r_child(node->r_child());
  if (node->parent() != nullptr) {
    if (node->parent()->l_child() == node)
      node->parent()->l_child(inorderSucc);
    else
      node->parent()->r_child(inorderSucc);
  }

  if (node->l_child() != nullptr)
    node->l_child()->parent(inorderSucc);
  if (node->r_child() != nullptr)
  node->r_child()->parent(inorderSucc);*/
  node->value(std::move(inorderSucc->value()));
  delete inorderSucc;
}

template <class T> inline Node<T> *BST<T>::search(const T &value) {
  Node<T> *currNode = _root;
  while (currNode != nullptr) {
    if (value == currNode->value())
      return currNode;
    if (value < currNode->value())
      currNode = currNode->l_child();
    else
      currNode = currNode->r_child();
  }
  return nullptr;
}
