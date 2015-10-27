//
// L_Stack.hpp
//
// Linked list stack implementation. Is capable of storing char or long type.
// User is expected to keep track of type being used.
//
// Project 7
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/30/2015
//

#ifndef _L_STACK
#define _L_STACK

#include <cstdlib>

class L_Stack {
   public:
      L_Stack();
      ~L_Stack();
      size_t size();
      void push(const char& var);
      void push(const long& var);
      char pop_c();
      long pop_l();
      char peek_c();
      long peek_l();
      void clear();

   private:
      struct Node {
         char c;
         long l;
         Node* next;
      };
      Node* first;
      size_t ls_size;
};

#endif
