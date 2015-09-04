//
// Set.hpp
//
// ADT that stores an unordered list of unique items.
//
// Project 2
// Created by Daniel Kozitza
// CSCI 301 section 2
// Due 09/11/2015
//

typdef int Item;

class Set {

	private:
		Item items[MAX_ITEMS];
		int size;

	public:
		Set();
		Set(const Set& s);
		void clear();
		void insert(Item i);
		void remove(Item i);
		void operator+=();
		void operator+();
		friend void operator<<();
		size_t size();
		bool find(Item i);

}
