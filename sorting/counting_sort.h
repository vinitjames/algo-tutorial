#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include <algorithm>
#include <vector>

inline void counting_sort(int* arr, const std::size_t len){
	if (arr == nullptr)
		return;
	int max = *std::max_element(arr, arr+len);
	std::vector<int> pos_arr(max+1);
	std::fill(pos_arr.begin(), pos_arr.end(), 0);
	for (int i=0; i<len; i++)
		pos_arr[arr[i]]++;
	int count_sum = pos_arr[0];
	pos_arr[0] = 0;
	for (int i = 1; i<=max ; i++){
	 	int temp = pos_arr[i];
		pos_arr[i] = pos_arr[i-1] + count_sum;
		count_sum = temp;
	}
	int temp_arr[len];
	std::copy(arr, arr+ len, temp_arr);
	for(int i=0; i<len; i++){
		arr[pos_arr[temp_arr[i]]] = temp_arr[i];
		pos_arr[temp_arr[i]]++;
	}
}

#endif /* COUNTING_SORT_H */

