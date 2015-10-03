//
// d_list.hpp
//
// ADT that stores an unordered linked list of Nodes. Each Node has an item, a
// pointer to the next Node, and a pointer to the previous node.
//
// Project 5
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 10/12/2015
//

#ifndef _D_LIST
#define _D_LIST

#include <iostream>

using namespace std;

class d_list {

   public:
		typedef char Item;

      d_list();
      ~d_list();
		void   empty();
      void   append(const Item& it);
		void   remove_last();
      friend ostream& operator<<(ostream &out_s, const d_list &s);

   private:
      struct Node {
         Item data;
         Node *next;
			Node *back;
      };

      Node *first;
		Node *last;

      Node* get_node(Node* b, Item d, Node* n);
};

#endif
