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

#include "sorters/insert.cpp"
#include "sorters/merge.cpp"
#include "sorters/quick.cpp"
#endif
