#include <algorithm>
#include <random>
#include <vector>

#include "insertion_sort.h"
#include "merge_sort.h"

#define TEST_VECTOR_SIZE 1000000000

int main(int argc, char *argv[]) {
  std::random_device rand_dev;
  std::mt19937 mt_engine{rand_dev()};
  std::uniform_int_distribution<int> dist{1, 1000};
  auto gen = [&mt_engine, &dist]() { return dist(mt_engine); };
  std::vector<int> test_vec(TEST_VECTOR_SIZE);
  std::generate(test_vec.begin(), test_vec.end(), gen);
  // for(auto &i : test_vec)
  //	std::cout<<i<<"\n";
  std::cout << "test started\n";
  // insertion_sort<std::vector<int>::iterator>(test_vec.begin(),
  // test_vec.end());
  merge_sort<int>(test_vec.data(), test_vec.size());
  std::cout << "test ended\n";
  // for(auto &i : test_vec)
  //	std::cout<<i<<"\n";
  return 0;
}
