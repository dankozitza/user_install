//
// prime_factorization.cpp
//
// Writes the factors of a positive integer in ascending order to stdout.
//
// Project 3
// Created by Daniel Kozitza
// account nuber 10540413
// CSCI 301 section 2
// Due 09/21/2015
//

#include "iostream"
#include "cassert"

using namespace std;

// char_to_int
//
// Converts a positive integer (0-9) in the char variable c to it's integer
// equivalent.
//
// Pre-condition: A positive integer (0-9) in variable c.
// Post-condition: Returns an integer equal to the number in c.
//
int char_to_int(char c) {
	// explode if c is not a number
	assert(c >= '0' && c <= '9');
	// convert the char in c to an int by subtracting the
	// decimal of '0' since '0' is the lowest in the range
	return c - '0';
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "USAGE: " << argv[0] << " INTEGER\n";
		return 0;
	}
	int n = 0;
	for (int i = 0; argv[1][i] != '\0'; i++)
		n = n * 10 + char_to_int(argv[1][i]);

	cout << "got int: `" << n << "`\n";
	return 0;
}
