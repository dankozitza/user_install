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
		Item   items[MAX_ITEMS];
		size_t size;

	public:
		Set();
		Set(const Set &s);
		void clear();
		void insert(const Item &i);
		void remove(const Item &i);
		void operator+=(const Set &addend);
		//Set operator+(const Set &s1, const Set &s2);
		//const Set operator+(const Set &other);
		friend ostream& operator<<(ostream &out_s, const Set &s);
		size_t size();
		bool find(Item i);

}
