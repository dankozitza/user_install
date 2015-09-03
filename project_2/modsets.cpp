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

int main() {
//	Set sets[MaxSets];
	char cmd = 'h';
	bool quit = false;
	int v;
	char c;
	int n;
	int i = 0;
	int ns[MaxNs]; // this is used to store a long list of Set indexes
	string s;

	print_help();
	do {
		cout << "enter command: ";
		cin >> cmd;
		switch (cmd) {
		case 'h':
			print_help();

			//getline(cin, s);
			//cout << "s: `" << s << "`\n";

			while (i < MaxNs && std::cin >> ns[i++]) {
			//while (c != '\n') {
				//cin >> v >> c;
				cout << "ns[i]: `" << ns[i] << "`\n";
				//cout << "c: `" << c << "`\n";
			}
			break;
		//case 'p':
		//	print_nonempty_sets(sets);
		//case 'i':
		//	insert(sets);
		//case 'r':
		//	remove(sets);
		//case 'u':
		//	set_union(sets, ns)
		case 'q':
			quit = true;
			break;
		}

	} while(!quit);
}
