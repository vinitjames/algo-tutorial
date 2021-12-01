#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H


#include <exception>
#include <iostream>
#include <vector>

/**
 * @brief      Inertion Sort templated function
 *
 * @details    The function takes generic 'begin' and 'end' iterator of anz container and sorts the element in \ asending or descending order depending on the passed flag. Inestion sort works by comparing nth element of an arry Arr  with a sorted Arr(0, n-1) array and  its correct position by performing atmost n-1 comparisons and if necessary corresponding swaps.   
 *
 * @param      start - type Iterator  end - type iterator 
 *
 * @return     return void
 */

template <typename Iterator>
inline void insertion_sort(Iterator begin, Iterator end){
	if(begin >= end) throw -1;
	for (Iterator it1 = begin+1; it1<end; it1++){
		Iterator cmp_it = it1;
		for(Iterator it2 = it1-1; it2>=begin; it2--){
			if (*cmp_it >= *it2){
				break;
			}
			std::swap(*cmp_it, *it2);
			cmp_it = it2;
		}
	}
}

#endif /* INSERTION_SORT_H */#include <algorithm>






