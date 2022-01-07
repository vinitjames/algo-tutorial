#include <stack>
#include <vector>

#include "../bst/bst.h"

template <typename T>
inline void _bst_sort_recursive(const Node<T>* root, std::vector<T>& vect) {
  if (root != nullptr) {
    _bst_sort_recursive(root->l_child(), vect);
    vect.push_back(root->value());
    _bst_sort_recursive(root->r_child(), vect);
  }
}

template <typename T>
inline void _bst_sort_iterative(const BST<T>& bst, std::vector<T>& vect) {
  std::stack<const Node<T>*> node_stack;
  const Node<T>* current = bst.root();
  while ((current != nullptr) || (!node_stack.empty())) {
    while (current != nullptr) {
      node_stack.push(current);
      current = current->l_child();
    }
    current = node_stack.top();
    node_stack.pop();
    vect.push_back(current->value());
    current = current->r_child();
  }
}

template <typename T>
inline std::vector<T> bst_sort(const BST<T>& bst, bool use_recursion = false) {
  std::vector<T> sorted_bst;
  if (use_recursion) {
    std::cout << "Recursive bst sort used" << std::endl;
    _bst_sort_recursive(bst.root(), sorted_bst);
  } else {
    std::cout << "Iterative bst sort used" << std::endl;
    _bst_sort_iterative(bst, sorted_bst);
  }
  return sorted_bst;
}
