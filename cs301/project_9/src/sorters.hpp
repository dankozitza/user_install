//
// sorters.hpp
//
// This namespace is a collection of sorting algorithms.
//
// Project 9
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 11/16/2015
//

#ifndef _SORTERS
#define _SORTERS

namespace sorters {

   template<class T>
   void exchange(T &v1, T &v2);

   template<class T, class SizeT, class CountT>
   CountT insert(T a[], SizeT a_size);
}

template<class T>
void sorters::exchange(T &v1, T &v2) {
   T tmp = v2;
   v2 = v1;
   v1 = tmp;
}

template<class T, class SizeT, class CountT>
CountT sorters::insert(T a[], SizeT a_size) {
   SizeT k, j;
   CountT cnt = 0;
   for(k = 1; k < a_size; ++k) {
      j = k;
      while (++cnt != 0 && j > 0 && a[j] < a[j-1]) {
         exchange<T>(a[j], a[j - 1]);
         --j;
      }
   }
   return cnt;
}


#endif
