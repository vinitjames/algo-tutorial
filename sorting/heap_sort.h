#ifndef HEAP_H
#define HEAP_H

#include <algorithm>

template <typename Iterator>
inline std::size_t get_largest_element_pos(const Iterator begin,
                                           const std::size_t root_pos,
                                           const std::size_t heap_size) {
  std::size_t left_child_pos = 2 * root_pos + 1;
  std::size_t right_child_pos = 2 * root_pos + 2;
  std::size_t largest_elem_pos = root_pos;
  if (left_child_pos >= heap_size) return largest_elem_pos;

  if (*(begin + left_child_pos) > *(begin + largest_elem_pos)) {
    largest_elem_pos = left_child_pos;
  }

  if (right_child_pos >= heap_size) {
    return largest_elem_pos;
  }

  if (*(begin + right_child_pos) > *(begin + largest_elem_pos)) {
    largest_elem_pos = right_child_pos;
  }
  return largest_elem_pos;
}

template <typename Iterator>
inline void max_heapify(Iterator begin, std::size_t root_pos,
                        std::size_t heap_size) {
  std::size_t largest_elem_pos =
      get_largest_element_pos(begin, root_pos, heap_size);
  if (largest_elem_pos == root_pos) return;
  std::swap(*(begin + largest_elem_pos), *(begin + root_pos));
  max_heapify(begin, largest_elem_pos, heap_size);
}

template <typename Iterator>
inline void build_max_heap(Iterator begin, Iterator end) {
  std::size_t heap_size = end - begin;
  for (int i = heap_size / 2 - 1; i >= 0; i--) {
    max_heapify(begin, i, heap_size);
  }
}

template <typename Iterator>
inline void heap_sort(Iterator begin, Iterator end) {
  int heap_size = end - begin;
  if (heap_size <= 0) throw -1;
  build_max_heap(begin, end);
  while (--heap_size >= 0) {
    std::swap(*begin, *(begin + heap_size));
    max_heapify(begin, 0, heap_size);
  }
}

#endif /* HEAP_H */
