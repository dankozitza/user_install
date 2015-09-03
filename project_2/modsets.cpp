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

const int MaxSets = 100;
const int MaxNs = 100;

//void set_union(char s[])

void print_help() {
	cout << "help\n";
}

void print_nonempty_sets(Set sets[]) const {
	bool not_one = true;
	for (int i = 0; i < MaxSets; i++) {
		if (sets[i].size() > 0) {
			not_one = false;
			cout << "set number " << i << " has ";
			cout << sets[i].size() << "elements\n";
		}
	}
	if (not_one) {
		cout << "all the sets are empty\n";
	}
}

void 

int main() {
//	Set sets[MaxSets];
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
		case 'q':
			quit = true;
			break;
		}

	} while(!quit);
}
