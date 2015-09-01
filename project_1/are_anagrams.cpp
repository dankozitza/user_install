//
// are_anagrams.cpp
//
// Prompts the user for two strings then checks to see if they are anagrams.
//
// Created by Daniel Kozitza
//

#include <iostream>
#include <ctype.h>
#include <map>

// is_lc_letter
//
// Returns true if the char c is a lowercase letter a-z. Otherwise returns
// false.
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
void define_set(std::map<char, int> &set) {
	for (int i = 'a'; i <= 'z'; i++)
		set[(char) i] = 0;
}

// sets_equal
//
// Compares keys a-z of each map.
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

	// get the first set of characters
	while (true) {
		char c;
		std::cin.get(c);
		c = tolower(c);
		if (c == '\n')
			break;
		if (is_lc_letter(c))
			first_set[c]++;
	}

	std::cout << "Enter the second string: ";

	// get the second set of characters
	while (true) {
		char c;
		std::cin.get(c);
		c = tolower(c);
		if (c == '\n')
			break;
		if (is_lc_letter(c))
			second_set[c]++;
	}

	if (sets_equal(first_set, second_set)) {
		std::cout << "They are anagrams!\n";
		return 0;
	}
	else {
		std::cout << "They are not anagrams.\n";
		return 1;
	}
}

void test_lc_letter() {

	if (is_lc_letter('a'))
		std::cout << "a is a letter!\n";
	else
		std::cout << "a is not a letter!\n";

	if (is_lc_letter('z'))
		std::cout << "z is a letter!\n";
	else
		std::cout << "z is not a letter!\n";

	if (is_lc_letter('`'))
		std::cout << "` is a letter!\n";
	else
		std::cout << "` is not a letter!\n";

	if (is_lc_letter('{'))
		std::cout << "{ is a letter!\n";
	else
		std::cout << "{ is not a letter!\n";
}
