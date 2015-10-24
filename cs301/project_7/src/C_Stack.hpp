//
// C_Stack.hpp
//
// Simple array based stack implementation.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

#ifndef _C_STACK
#define _C_STACK

#include <cassert>
#include <cstdlib>

using namespace std;

class C_Stack {
   public:
      typedef char Item;
      static const size_t STACK_CAP = 13;

      C_Stack();
      size_t size();
      void push(const Item& it);
      Item pop();
      Item peek();
      void clear();

   private:
      Item items[STACK_CAP];
      size_t s_size;
};

#endif
