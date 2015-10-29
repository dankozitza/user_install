//
// L_Stack.cpp
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

#include "L_Stack.hpp"

L_Stack::L_Stack() {
   first = NULL;
   ls_size = 0;
}

L_Stack::~L_Stack() {
   clear();
}

size_t L_Stack::size() {
   return ls_size;
}

void L_Stack::push(const char& var) {
   Node* tmp = new Node;
   tmp->c = var;
   tmp->next = first;
   first = tmp;
   ++ls_size;
}

void L_Stack::push(const long& var) {
   Node* tmp = new Node;
   tmp->l = var;
   tmp->next = first;
   first = tmp;
   ++ls_size;
}

char L_Stack::pop_c() {
    Node* tmp = first;
   char tmp_c = tmp->c;
   first = first->next;
   delete tmp;
   --ls_size;
   return tmp_c;  
}

long L_Stack::pop_l() {
   Node* tmp = first;
   long tmp_l = tmp->l;
   first = first->next;
   delete tmp;
   --ls_size;
   return tmp_l;
}

char L_Stack::peek_c() {
   return first->c;
}

long L_Stack::peek_l() {
   return first->l;
}

void L_Stack::clear() {
   Node* tmp;
   while (first != NULL) {
      tmp = first;
      first = first->next;
      delete tmp;
   }
   ls_size = 0;
}
