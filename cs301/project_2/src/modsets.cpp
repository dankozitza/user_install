//
// modsets.cpp
//
// Menu-driven program for modifying sets of items.
//
// Project 2
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 09/11/2015
//

#include "Set.hpp"

using namespace std;

const size_t MAX_SETS = 3;

void print_help() {
	cout << "\nmodsets is a menu-driven program for modifying sets of items.\n";
	cout << "\nCommands:\n";
	cout << "   h          - print this help message\n";
	cout << "   p          - print sets that have items in them\n";
	cout << "   i v n      - insert item v into set n\n";
	cout << "   r v n      - remove item v from set n\n";
	cout << "   + n1 n2 n3 - assign the union of set n1 and set n2 to set n3\n";
	cout << "   - n1 n2 n3 - assign the intersection of "
                        << "set n1 and set n2 to set n3\n";
	cout << "   m n1 n2    - copy set n1 to set n2\n";
	cout << "   s n        - print the size of set n\n";
	cout << "   f v n      - determine if item v is found in set n\n";
	cout << "   w n        - write set n to stdout\n";
	cout << "   c n        - clear set n\n";
	cout << "   q          - exit this program\n\n";
}

void print_nonempty_sets(Set sets[]) {
	bool none = true;
	for (int i = 0; i < MAX_SETS; i++) {
		if (sets[i].size() > 0) {
			none = false;
			cout << "set " << i << " has " << sets[i].size() << " items\n";
		}
	}
	if (none) {
		cout << "all the sets (" << 0 << "..." << MAX_SETS - 1 << ") are empty\n";
	}
}

void print_found(Set& set, int v) {
	if (set.found(v))
		cout << "yes\n";
	else
		cout << "no\n";
}

int main() {
	Set  sets[MAX_SETS];
	int  v, n, n1, n2;
	char cmd;

	print_help();
	do {
		cout << "enter command: ";
		cin >> cmd;
		switch (cmd) {
		case 'h':
			print_help();
			break;
		case 'p':
			print_nonempty_sets(sets);
			break;
		case 'i':
			cin >> v >> n;
			sets[n].insert(v);
			break;
		case 'r':
			cin >> v >> n;
			sets[n].remove(v);
			break;
		case '+':
			cin >> n1 >> n2 >> n;
			sets[n] = sets[n1] + sets[n2];
			break;
		case '-':
			cin >> n1 >> n2 >> n;
			sets[n] = sets[n1] - sets[n2];
			break;
		case 'm':
			cin >> n1 >> n2;
			sets[n2] = Set(sets[n1]);
			break;
		case 's':
			cin >> n;
			cout << sets[n].size() << endl;
			break;
		case 'f':
			cin >> v >> n;
			print_found(sets[n], v);
			break;
		case 'w':
			cin >> n;
			cout << sets[n] << endl;
			break;
		case 'c':
			cin >> n;
			sets[n].clear();
			break;
		}

	} while(cmd != 'q');

	return EXIT_SUCCESS;
}
