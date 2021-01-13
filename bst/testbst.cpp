#include "bst.h"

int main(int argc, char *argv[]) {
  BST<float> testbst;
  testbst.insert(5.3);
  testbst.insert(5.23);
  testbst.insert(5.28);

  testbst.insert(6.1);
  testbst.insert(6);
  testbst.insert(100);

  std::cout << "max " << testbst.max()->value() << '\n';
  std::cout << "max parent " << testbst.max()->parent()->value() << '\n';
  std::cout << "min " << testbst.min()->value() << '\n';
  std::cout << "min parent " << testbst.min()->parent()->value() << '\n';
  return 0;
}
