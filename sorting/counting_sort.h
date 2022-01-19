#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

#include <algorithm>
#include <vector>

inline void counting_sort(int* arr, const std::size_t& len,
						  const int& digit, const int& base){
	if (arr == nullptr)
		return;
	std::vector<int> pos_arr(base);
	std::fill(pos_arr.begin(), pos_arr.end(), 0);
	unsigned long divisor = pow(base, digit);  
	for (int i=0; i<len; i++)
		pos_arr[(arr[i]/divisor)%base]++;
	int count_sum = pos_arr[0];
	pos_arr[0] = 0;
	for (int i = 1; i<base ; i++){
	 	int temp = pos_arr[i];
		pos_arr[i] = pos_arr[i-1] + count_sum;
		count_sum = temp;
	}
	int temp_arr[len];
	std::copy(arr, arr+ len, temp_arr);
	for(int i=0; i<len; i++){
		unsigned long digit_of_base = (temp_arr[i]/divisor)%base;
		arr[pos_arr[digit_of_base]] = temp_arr[i];
		pos_arr[digit_of_base]++;
	}
}



#endif /* COUNTING_SORT_H */

