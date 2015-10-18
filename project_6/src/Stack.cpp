//
// Stack.cpp
//
// Simple array based stack implementation.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

Stack::Stack() {
   s_size = 0;
}

size_t Stack::size() {
   return s_size;
}

void Stack::push(const Item& it) {
   assert(s_size < STACK_CAP);

   items[s_size++] = it;
}

Item Stack::pop() {
   return items[--s_size];
}

void Stack::clear() {
   s_size = 0;
}
