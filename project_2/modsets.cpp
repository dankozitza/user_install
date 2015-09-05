//
// modsets.cpp
//
// Menu-driven program for modifying sets of items
//
// Project 2
// Created by Daniel Kozitza
// CSCI 301 section 2
// Due 09/11/2015
//

#include <cassert>
#include <iostream>
//#include "Set.hpp"

using namespace std;

const int MAX_SETS = 100;

void print_help() {
	cout << "help\n";
}

void print_nonempty_sets(Set sets[]) const {
	bool none = true;
	for (int i = 0; i < MAX_SETS; i++) {
		if (sets[i].size() > 0) {
			none = false;
			cout << "set number " << i << " has ";
			cout << sets[i].size() << "elements\n";
		}
	}
	if (none) {
		cout << "all the sets are empty\n";
	}
}

void print_present(const Set& set, int v) {
	for (int i = 0; i < set.size(); i++) {
		if (set[i] == v) {
			cout << "yes\n";
			return;
		}
	}
	cout << "no\n";
}

int main() {
//	Set sets[MAX_SETS];
	char cmd = 'h';
	bool quit = false;
	int v, n, n1, n2, n3;

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
		case 'u':
			cin >> n1 >> n2 >> n3;
			sets[n3] = sets[n1] + sets[n2];
			break;
		case 's':
			cin >> n;
			cout << sets[n].size() << endl;
			break;
		case 'p':
			cin >> v >> n;
			print_present(sets[n], v);
			break;
		case 'w':
			cin >> n;
			cout << sets[n] << endl;
			break;
		case 'e':
			cin >> v >> n;
			sets[n].remove(v);
			break;
		case 'q':
			quit = true;
			break;
		}

	} while(!quit);
}
