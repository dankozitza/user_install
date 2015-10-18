//
// Set.hpp
//
// ADT that stores an unordered list of unique items.
//
// Project 2
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 09/11/2015
//

#ifndef _SET
#define _SET

#include <cstdlib>  // provides size_t
#include <iostream> // provides ostream

using namespace std;

class Set {

	public:
		typedef int Item;
		static const size_t MAX_ITEMS = 100;

		Set();
		Set(const Set &s);
		void clear();
		bool found(const Item &it);
		void insert(const Item &it);
		void remove(const Item &it);
		void operator+=(const Set &s2);
		Set operator+(const Set &s2);
		void operator-=(const Set &s2);
		Set operator-(const Set &s2);
		size_t size();
		friend ostream& operator<<(ostream &out_s, const Set &s);

	private:
		Item   items[MAX_ITEMS];
		size_t i_size;

};

#endif
