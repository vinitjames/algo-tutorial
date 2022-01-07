#include <iostream>
#include <string>

#include "../avl/avl.h"

int main(int argc, char* argv[]) {
  AVL<float> avl1;
  avl1.insert(5.5);
  avl1.insert(5.2);
  avl1.insert(5.1);
  avl1.insert(5.9);

  AVL<float>::node_type* max_node = avl1.max();

  std::cout << "max of bst: " << avl1.max()->value()
            << " min of bst: " << avl1.min()->value() << std::endl;
  avl1.forEach([](AVL<float>::node_type* node) {
    std::cout << node->value() << std::endl;
  });
  return 0;
}
