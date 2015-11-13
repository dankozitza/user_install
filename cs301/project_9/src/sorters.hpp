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

using namespace std;

namespace sorters {

   template<class T>
   void exchange(T &v1, T &v2);

   template<class T, class SizeT, class CountT>
   CountT insert(T a[], SizeT a_size);

   template<class T, class SizeT, class CountT>
   CountT merge(T a[], SizeT a_size);
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

template<class T, class SizeT, class CountT>
CountT sorters::merge(T a[], SizeT a_size) {
   T *tmp;
   SizeT low = 0, med = a_size / 2;
   SizeT j = 0, k = med;
   SizeT tmp_size = 0;

   cout << "a[low ... mid-1]:\n   ";
   for (int i = 0; i < med; i++)
      cout << a[i] << " ";
   cout << endl;

   cout << "a[med ... a_size-1]:\n   ";
   for (int i = med; i < a_size; ++i)
      cout << a[i] << " ";
   cout << endl;

   tmp = new T[a_size];
   while(j < med && k < a_size) {
      if (a[j] < a[k])
         tmp[tmp_size++] = a[j++];
      else
         tmp[tmp_size++] = a[k++];
   }

   cout << "tmp[]:\n";
   for (int i = 0; i < tmp_size; ++i)
      cout << tmp[i] << " ";

   delete []tmp;
}

#endif
