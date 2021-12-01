#ifndef MERGE_SORT_H
#define MERGE_SORT_H


#include <algorithm>
#include <iostream>
#include <exception>

/**
 * @brief      Merge Sort templated function
 *
 * @details    Merge sort funcion takes begin and end iterators of any container and sorts it based on merge sort 
               algorithm. In Merge sort the algorithm recursively divides the array into two arrays of half size until arraz of single elements and then the array  are merged pairwise to form a sorted array.  
 *
 * @param      start - type Iterator  end - type iterator 
 *
 * @return     return void
 */

template <typename T>
inline void merge(T* arr, const std::size_t offset, const std::size_t size){
	T* temp_arr1 = new T[offset];
	T* temp_arr2 = new T[size - offset];
	std::copy(arr, arr + offset, temp_arr1);
	std::copy(arr + offset, arr + size, temp_arr2);
	std::size_t i = 0, iter1 = 0, iter2 = 0;
	while((iter1 < offset)&&(iter2 < size - offset)){
		if (temp_arr1[iter1] < temp_arr2[iter2]){
			arr[i++] = temp_arr1[iter1++];
		}
		else {
			arr[i++] = temp_arr2[iter2++];
		}
	}
	while (iter1 < offset){
		arr[i++] = temp_arr1[iter1++];
	}
	while (iter2 < size - offset){
		arr[i++] = temp_arr2[iter2++];
	}
	delete[] temp_arr1;
	delete[] temp_arr2;
}

template <typename T>
inline void  merge_sort(T* arr, std::size_t size = 0){
	if (size == 0) throw -1;
	if(size == 1) return;
    size_t offset = size/2; 
	merge_sort(arr , offset);
	merge_sort(arr + offset, size - offset);
	return merge(arr, offset, size);
  }


#endif /* MERGE_SORT_H */
