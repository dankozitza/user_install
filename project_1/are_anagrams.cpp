//
// are_anagrams.cpp
//
// Prompts the user for two strings then checks to see if they are anagrams.
//
// Project 1
// Created by Daniel Kozitza
// CSCI 301 section 2
// Due 09/02/2015
//

#include <cassert>
#include <ctype.h>
#include <iostream>
#include <map>

const int LineMaxLength = 60;

// is_lc_letter
//
// Returns true if the char c is a lowercase letter a-z. Otherwise returns
// false.
//
// Pre-condition: A variable c of type char.
// Post-condition: Returns a true or false value declaring whether
//                 c is a lowercase letter or not.
//
bool is_lc_letter(const char c) {

	if ((int) 'a' <= (int) c && (int) 'z' >= (int) c)
		return true;

	return false;
}

// define_set
//
// Sets the keys a-z to 0.
//
// Pre-condition: A pointer to a map with char keys and int values.
// Post-condition: The map with key-values a-z set to 0.
//
void define_set(std::map<char, int> &set) {
	for (int i = 'a'; i <= 'z'; i++)
		set[(char) i] = 0;
}

// get_set
//
// Gets the set from stdin.
//
// Pre-condition: A pointer to a stream and a pointer to a map with char keys
//                and int values.
// Post-condition: The istream with one line removed and the map with keys a-z
//                 incremented once for each a-z character from the stream.
//
void get_set(std::istream &in, std::map<char, int> &set) {
	int cnt = 1;
	while (true) {
		char c;
		in.get(c);
		c = tolower(c);
		if (c == '\n')
			break;
		assert(cnt < LineMaxLength);
		cnt++;
		if (is_lc_letter(c))
			set[c]++;
	}
	assert(cnt > 1);
}

// sets_equal
//
// Compares keys a-z of each map.
//
// Pre-condition: Two maps with char keys and int values.
// Post-condition: Returns a true or false value declaring whether the map's
//                 keys a-z contain the same values.
//
bool sets_equal(std::map<char, int> set_1, std::map<char, int> set_2) {
	for (int i = 'a'; i <= 'z'; i++) {
		if (set_1[(char) i] != set_2[(char) i])
			return false;
	}
	return true;
}

int main() {

	std::map<char, int> first_set;
	std::map<char, int> second_set;
	define_set(first_set);
	define_set(second_set);

	std::cout << "Enter the first string:  ";
	get_set(std::cin, first_set);

	std::cout << "Enter the second string: ";
	get_set(std::cin, second_set);

	if (sets_equal(first_set, second_set)) {
		std::cout << "They are anagrams!\n";
		return 0;
	}
	else {
		std::cout << "They are not anagrams.\n";
		return 1;
	}
}
