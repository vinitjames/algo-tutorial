#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <math.h>

#include <algorithm>

#include "counting_sort.h"

inline void radix_sort(int* arr, const std::size_t& len, const int& radix) {
  if (arr == nullptr) return;
  int max = *std::max_element(arr, arr + len);
  int digits = int(log(max) / log(radix) + 1.0);

  for (int i = 0; i < digits; i++) {
    counting_sort(arr, len, i, radix);
  }
}

#endif /* RADIX_SORT_H */
