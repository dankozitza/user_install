//
// C_Stack.cpp
//
// Simple array based stack implementation.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

#include "C_Stack.hpp"

C_Stack::C_Stack() {
   s_size = 0;
}

size_t C_Stack::size() {
   return s_size;
}

void C_Stack::push(const Item& it) {
   assert(s_size < STACK_CAP);

   items[s_size++] = it;
}

C_Stack::Item C_Stack::pop() {
   return items[--s_size];
}

C_Stack::Item C_Stack::peek() {
   return items[s_size - 1];
}

void C_Stack::clear() {
   s_size = 0;
}
