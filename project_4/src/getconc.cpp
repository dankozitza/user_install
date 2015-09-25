//
//	getconc.cpp
//



// Project 4
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 09/30/2015
//

#include <iostream>
#include <fstream>
#include "concordance.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	ifstream ifs;
	char word[concordance::WORD_MAX];

	if (argc != 2) {
		cout << "USAGE: " << argv[0] << " FILE\n";
		return 0;
	}

	ifs.open(argv[1]);

	while (!ifs.eof()) {
		char c;
		ifs.get(c);

		// convert any upper case characters to lower case
		if (65 <= c && c <= 91)
			c += 32;

		// this loop takes one word from ifs
		int index = 0;
		while (97 <= c && c <= 122) {
			// if the size has not exceeded max then add characters to word.
			// otherwise just run through the rest of the letters in this word.
			if (index < concordance::WORD_MAX - 1) {
				word[index] = c;
				word[index+1] = '\0';
				index++;
			}

			// this should break if eof happens
			ifs.get(c);
			cout << "`" << c << "`\n";
			//cout << endl;
			// convert again
			if (65 <= c && c <= 91)
				c += 32;
		}
		if (index > 0) {
			// word is ready to be placed in ADT
			cout << "'" << word << "'";
		}
	}

	return 0;
}
