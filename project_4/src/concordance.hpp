//
// concordance.hpp
//
// ADT that stores an ordered linked list of Nodes. Each Node has an item (in
// this case a word), a count (the number of times that item has been inserted),
// and a pointer to the next Node.
//
// Project 4
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 09/30/2015
//

#ifndef _CONCORDANCE
#define _CONCORDANCE

#include <iostream> // provides ostream

using namespace std;

class concordance {

	public:
		static const size_t ITEM_MAX = 9;
		typedef char[ITEM_MAX] Item;

		concordance();
		~concordance();
		void   insert(const Item &it);
		int    get_count(const Item &it);
		size_t length();
		friend ostream& operator<<(ostream &out_s, const concordance &s);

	private:
		struct Node {
			Item item;
			int count;
			Node *next;
		}
		Node *first;
		Node* get_node(const Item &it, Node* next_link);

};

#endif
