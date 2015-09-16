//
// even_backwards.cpp
//
// A program that takes a positive even integer and outputs the even digits
// backwards.
//
// Project 3
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 09/21/2015
//

#include <iostream>
#include <cassert>

using namespace std;

int char_to_int(char c) {
	// explode if c is not a number
	assert(c >= 48 && c <= 57);
	// convert the char in c to an int by subtracting 48
	return c - 48;
}

void even_backwards(int n) {
	if (n < 10) {
		cout << "here\n";
		if (n < 1)
			return;
		if (n % 2 == 0)
			cout << n;
		else
			return;
	}
	even_backwards(n / 10);
	if ((n % 10) % 2 == 0)
		cout << n % 10;
	return;
}

int main(int argc, char *argv[]) {
	assert(argc == 2);

	int n = 0, i = 0;
	while (argv[1][i] != '\0') {
		n = n * 10 + char_to_int(argv[1][i]);
		i++;
	}

	cout << "got integer: `" << n << "`\n";

	cout << "even_backwards: `";
	even_backwards(n);
	cout << "`\n";

	return 0;
}
