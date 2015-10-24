//
// N_Stack.cpp
//
// Simple array based stack implementation.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

#include "N_Stack.hpp"

N_Stack::N_Stack() {
   s_size = 0;
}

size_t N_Stack::size() {
   return s_size;
}

void N_Stack::push(const Item& it) {
   assert(s_size < STACK_CAP);

   items[s_size++] = it;
}

N_Stack::Item N_Stack::pop() {
   return items[--s_size];
}

N_Stack::Item N_Stack::peek() {
   return items[s_size-1];
}

void N_Stack::clear() {
   s_size = 0;
}
