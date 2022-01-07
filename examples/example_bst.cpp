#include <iostream>
#include <string>

#include "../bst/bst.h"

int main(int argc, char* argv[]) {
  BST<Node, float, int> bst1;
  bst1.insert(5.5);
  bst1.insert(5.1);
  bst1.insert(5.2);
  bst1.insert(5.7);
  BST<Node, float, int>::node_type* max_node = bst1.max();
  BST<Node, float, int>::node_type* min_node = bst1.min();
  std::cout << "max of bst: " << max_node->value()
            << " min of bst: " << min_node->value();
  bst1.forEach([](BST<Node, float, int>::node_type* node) {
    std::cout << node->value() << std::endl;
  });
  bst1.removeNode(5.7);
  bst1.removeNode(5.1);
  std::cout << "max of bst: " << bst1.max()->value()
            << " min of bst: " << bst1.min()->value();
  return 0;
}
