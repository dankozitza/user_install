//
// even_backwards.cpp
//
// A program that takes a positive even integer and outputs the even digits
// backwards
//
// Project 3
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 09/21/2015
//

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	int n = 0, i = 0;
	while (argv[1][i] != '\0') {
		// explode if a number is not given
		assert(argv[1][i] >= 48 && argv[1][i] <= 57);
		// convert the char in argv[1][i] to an int by subtracting 48
		n = n * 10 + argv[1][i] - 48;
		i++;
	}

	cout << "got integer: `" << n << "`\n";

	return 0;
}
