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
#include <iomanip>
#include "concordance.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	ifstream ifs;
	concordance::Word word;
	concordance conc;

	if (argc != 2) {
		cout << "USAGE: " << argv[0] << " FILE\n";
		return 0;
	}

	cout << "`" << argv[1] << "`\n";
	if (argv[1] == "TEST") {
		concordance::Word wrd = {'h', 'h', 'h', '\0', '\0', '\0', '\0', '\0'};
		conc.insert(wrd);
		cout << "get_count(\"hhh\"): `" << conc.get_count(wrd) << "`\n";
		return 0;
	}
	else {
		cout << "got here\n";
	}

	ifs.open(argv[1]);
	if (!ifs.is_open()) {
		cout << "could not open file " << argv[1] << endl;
		return 0;
	}

	int i;
	char c;
	while (!ifs.eof()) {
		ifs.get(c);

		// convert any upper case characters to lower case
		if ('A' <= c && c <= 'Z')
			c += 32;

		// this block takes one word from ifs
		if ('a' <= c && c <= 'z') {
			i = 0;
			word[i] = c;
			word[i+1] = '\0';
			i++;
		
			while (!ifs.eof()) {
				ifs.get(c);
				// convert again
				if ('A' <= c && c <= 'Z')
					c += 32;

				if (!('a' <= c && c <= 'z'))
					break;

				// if the size is not over capacity then add characters to word.
				// otherwise just run through the rest of the letters in this word.
				if (i < concordance::WORD_CAP - 1) {
					word[i] = c;
					word[i+1] = '\0';
					i++;
				}
			}

			// word is ready to be placed in ADT
			//cout << "'" << word << "'";
			conc.insert(word);
		}
	}

	cout << conc;

	return 0;
}
