//
// Set.cpp
//
// ADT that stores an unordered list of unique items.
//
// Project 2
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 09/11/2015
//

#include <cassert>  // provides assert()
#include <iomanip>  // provides setw()
#include "Set.hpp"

Set::Set() {
	i_size = 0;
}

Set::Set(const Set &s) {
	*this = s;
}

void Set::clear() {
	i_size = 0;
}

bool Set::found(const Item &it) {
	for (size_t i = 0; i < i_size; i++) {
		if (items[i] == it)
			return true;
	}
	return false;
}

void Set::insert(const Item &it) {
	assert(i_size < MAX_ITEMS);
	if (!found(it))
		items[i_size++] = it;
}

void Set::remove(const Item &it) {
	for (size_t i = 0; i < i_size; i++) {
		if (items[i] == it) {
			items[i] = items[i_size-1];
			i_size--;
			return;
		}
	}
}

size_t Set::size() {
	return i_size;
}

void Set::operator+=(const Set &s2) {
	size_t a_size = s2.i_size;
	for (size_t i = 0; i < a_size; i++)
		insert(s2.items[i]);
}

Set Set::operator+(const Set &s2) {
	Set new_set = *this;
	new_set += s2;
	return new_set;
}

void Set::operator-=(const Set &s2) {
	size_t a_size = s2.i_size;
	for (size_t i = 0; i < a_size; i++)
		remove(s2.items[i]);
}

Set Set::operator-(const Set &s2) {
	Set new_set = *this;
	new_set -= s2;
	return new_set;
}

ostream& operator<<(ostream &out_s, const Set &s) {
	out_s << "{";
	if (s.i_size > 0) {
		for (size_t i = 0; i < s.i_size - 1; i++)
			out_s << setw(1) << s.items[i] << ", ";
		out_s << setw(1) << s.items[s.i_size - 1];
	}
	out_s << "}";
	return out_s;
}
