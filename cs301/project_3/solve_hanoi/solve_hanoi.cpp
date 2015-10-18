//
// solve_hanoi.cpp
//
// takes the integer arguments, disks, source, and destination then describes
// to the user how to move disks from source peg to destination peg.
//
// Project 3
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 09/21/2015
//

#include <iostream>

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
	if (c < '0' || c > '9') {
		cout << "invalid input! positive integers only.\n";
		throw;
	}
	// convert the char in c to an int by subtracting the
	// decimal of '0' since '0' is the lowest in the range
	return c - '0';
}

// hanoi
//
// Given the number of disks, source peg and destination peg this function will
// write out instructions for the user to move the disks from the source peg to
// the destination peg.
//
// Pre-condition: Number of disks n and integers from 1 to 3 src and dest.
// Post-condition: Instructions written to stdout.
//
void hanoi(int n, int src, int dest) {
	if (n == 0) {
		cout << "No disks!\n";
		return;
	}
	if (n == 1) {
		cout << "Move disk from peg " << src << " to peg " << dest << ".\n";
		return
	}
	else {
		int other = 6 - src - dest;
		hanoi(n-1, src, other);
		cout << "Move disk from peg " << src << " to peg " << dest << ".\n";
		hanoi(n-1, other, dest);
	}
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "USAGE: " << argv[0] << " DISKS SOURCE DESTINATION\n";
		return 0;
	}

	int n = 0, s, d;

	// get n, s, and d from the command line arguments
	for (int i = 0; argv[1][i] != '\0'; i++)
		n = n * 10 + char_to_int(argv[1][i]);
	for (int i = 0; argv[2][i] != '\0'; i++)
		s = s * 10 + char_to_int(argv[2][i]);
	for (int i = 0; argv[3][i] != '\0'; i++)
		d = d * 10 + char_to_int(argv[3][i]);

	cout << "got n: " << n << " s: " << s << " d: " << d << "\n";

	hanoi(n, s, d);

	return 0;
}
