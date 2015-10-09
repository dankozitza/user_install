//
// d_list.cpp
//
// ADT that stores an unordered linked list of Nodes. Each Node has an item, a
// pointer to the next Node, and a pointer to the previous node.
//
// Project 5
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/12/2015
//

#include "d_list.hpp"

d_list::d_list() {
   first = NULL;
   last = NULL;
}

d_list::~d_list() {
   Node* tmp;
   while (first != NULL) {
      tmp = first;
      first = first->next;
      delete tmp;
   }
}

// empty
//
// Reports if the function is empty.
//
// Pre-condition: a d_list object
// Post-condition: a true or false returned
//
bool d_list::empty() {
   if (first == NULL)
      return true;
   else
      return false;
}

// append
//
// Adds an item to the end of the list.
//
// Pre-condition: an item
// Post-condition: that item entered into the list
//
void d_list::append(const Item& it) {
   if (first == NULL) {
      first = get_node(NULL, it, NULL);
      last = first;
   }
   else {
      last->next = get_node(last, it, NULL);
      last = last->next;
   }
}

// remove_last
//
// Removes the last item from the list if it exists. This function has no
// effect on an empty list.
//
// Pre-condition: a d_list object
// Post-condition: that object without it's list item
//
void remove_last() {
   Node* tmp;
   if (last != NULL) {
      tmp = last;
      last = last->back;
      last->next = NULL;
      delete tmp;
   }
}

// operator<<
//
// Writes the items in the list from first to last to the output stream out_s.
//
// Pre-condition: a d_list object
// Post-condition: that object written to out_s
//
friend ostream& operator<<(ostream& out_s, const d_list& dl) {
   d_list::Node* tmp = source.first;
   while (tmp != NULL) {
      out_s << tmp->data;
      tmp = tmp->next;
   }
}

// get_node
//
// Helper function for d_list. Creates a new node and returns a pointer to it.
//
// Pre-condition: a back pointer b, an item d, and a next pointer n
// Post-condition: a pointer to a new node
//
Node* d_list::get_node(Node* b, const Item& d, Node* n) {
   Node* tmp = new Node;
   tmp->back = b;
   tmp->data = d;
   tmp->next = n;
   return tmp;
}
