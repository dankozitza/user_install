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

#include <cassert>

using namespace std;

namespace sorters {
   template<class T>
   void exchange(T &v1, T &v2);

   template<class T, class SizeT, class CountT>
   CountT insert(T a[], SizeT a_size);

   template<class T, class SizeT, class CountT>
   CountT merge(T a[], SizeT a_size);

   template<class T, class SizeT, class CountT>
   CountT quick(T a[], SizeT a_size);
}

template<class T>
void sorters::exchange(T &v1, T &v2) {
   T tmp = v2;
   v2 = v1;
   v1 = tmp;
}

// insert
//
//
//
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
CountT r_merge(T a[], SizeT low, SizeT high);

template<class T, class SizeT>
void real_merge(T a[], SizeT low, SizeT mid, SizeT high);

// merge
//
//
//
template<class T, class SizeT, class CountT>
CountT sorters::merge(T a[], SizeT a_size) {
   return r_merge<T, SizeT, CountT>(a, 0, a_size - 1);
}

template<class T, class SizeT, class CountT>
CountT r_merge(T a[], SizeT low, SizeT high) {
   SizeT mid = (low + high) / 2;
   CountT count = 0;
   if (low < high) {
      count += r_merge<T, SizeT, CountT>(a, low, mid);
      count += r_merge<T, SizeT, CountT>(a, mid + 1, high);
      real_merge<T, SizeT>(a, low, mid, high);
      count += 2 * (high - low + 1);
   }
   return count;
}

template<class T, class SizeT>
void real_merge(T a[], SizeT low, SizeT mid, SizeT high) {
   SizeT j = low, k = mid + 1;
   SizeT tmp_size = high - low + 1;
   SizeT tmp_index = 0;
   T *tmp;

   tmp = new T[tmp_size];
   while(j < mid + 1 && k < high + 1) {
      if (a[j] < a[k])
         tmp[tmp_index++] = a[j++];
      else
         tmp[tmp_index++] = a[k++];
   }

   while(j < mid + 1)
      tmp[tmp_index++] = a[j++];
   while(k < high + 1)
      tmp[tmp_index++] = a[k++];

   assert(tmp_index == tmp_size);
   tmp_index = 0;
   for (int i = low; i <= high; ++i)
      a[i] = tmp[tmp_index++];

   delete []tmp;
}

template<class T, class SizeT, class CountT>
CountT r_quick(T a[], SizeT low, SizeT high);

template<class T, class SizeT>
void partition(T a[], SizeT low, SizeT high, T pivot, SizeT &i, SizeT &j);

// quick
//
//
//
template<class T, class SizeT, class CountT>
CountT sorters::quick(T a[], SizeT a_size) {
   return r_quick<T, SizeT, CountT>(a, 0, a_size - 1);
}

template<class T, class SizeT, class CountT>
CountT r_quick(T a[], SizeT low, SizeT high) {
   CountT count = 0;
   SizeT i, j;
   if (low < high) {
      T pivot = a[low];
      partition<T, SizeT>(a, low, high, pivot, i, j);
      count += high - low + 1;

      count += r_quick<T, SizeT, CountT>(a, low, i);
      count += r_quick<T, SizeT, CountT>(a, j, high);
   }
   return count;
}

template<class T, class SizeT>
void partition(T a[], SizeT low, SizeT high, T pivot, SizeT &i, SizeT &j) {
   SizeT lasts1 = low, firstU = low, firsts3 = high + 1;
   while (firstU < firsts3) {
      if (a[firstU] < pivot) // s1
         sorters::exchange(a[firstU++], a[lasts1++]);
      else if (a[firstU] == pivot) // s2
         ++firstU;
      else // s3
         sorters::exchange(a[firstU], a[--firsts3]);
   }
   if (lasts1 > 0)
      --lasts1;
   i = lasts1;
   j = firsts3;
}

#endif
