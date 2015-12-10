//
// sorters.hpp
//
// This namespace is a collection of sorting algorithms.
//
// Project 12
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 12/11/2015
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

   template<class T, class SizeT, class CountT>
   CountT heap(T a[], SizeT a_size);
}

#include "sorters/insert.tpp"
#include "sorters/merge.tpp"
#include "sorters/quick.tpp"
#include "sorters/heap.tpp"
#endif
