//
// concordance.cpp
//
// ADT that stores an ordered linked list of Nodes. Each Node has a word, a
// count (the number of times that item has been inserted), and a pointer to
// the next Node.
//
// Project 4
// Created by Daniel Kozitza
// account number 10540413
// CSCI 301 section 2
// Due 09/30/2015
//

#include <iomanip>
#include "concordance.hpp"

bool less_than(const char a[], const char b[]);
bool r_less_than(const char a[], const char b[], int i);
bool equals(const char a[], const char b[]);
bool r_equals(const char a[], const char b[], int i);

concordance::concordance() {
	first = NULL;
}

// insert
//
// Inserts `word` into the list in it's appropriate place alphabetically.
//
// Pre-condition: A word.
// Post-condition: That word inserted into the list.
//
void concordance::insert(Word word) {
	Node* pre;
	if (first == NULL || less_than(word, first->word)) {
		first = get_node(word, 1, first);
		return;
	}
	if (equals(word, first->word)) {
		first->count++;
		return;
	}

	// if word is 2nd through 2nd to last
	pre = first;
	while (pre->next != NULL) {
		if (less_than(word, pre->next->word)) {
			pre->next = get_node(word, 1, pre->next);
			return;
		}
		if (equals(word, pre->next->word)) {
			pre->next->count++;
			return;
		}
		pre = pre->next;
	}

	// if word is the last alphabetically
	pre->next = get_node(word, 1, NULL);
}

// get_count
//
// Returns the number of times `word` appears.
//
// Pre-condition: A word.
// Post-condition: Returns the count for that word.
//
int concordance::get_count(Word word) {
	Node* p = first;
	while(p != NULL) {
		if (equals(p->word, word))
			return p->count;
		p = p->next;
	}
	return 0;
}

// length
//
// Returns the length of the list.
//
// Pre-condition: none
// Post-condition: returns the length.
//
size_t concordance::length() {
	Node* p = first;
	size_t cnt = 0;
	while (p != NULL) {
		cnt++;
		p = p->next;
	}
	return cnt;
}

// get_node
//
// Tool used to create a new node.
//
// Pre-condition: a word w, it's count, and a pointer to next.
// Post-condition: returns a pointer to a new node.
//
concordance::Node* concordance::get_node(Word w, int cnt, Node* p) {
	Node* tmp = new Node;
	for (int i = 0; i < WORD_CAP; i++)
		tmp->word[i] = w[i];
	tmp->count = cnt;
	tmp->next = p;
	return tmp;
}

// ~concordance
//
// Delete all the nodes.
//
// Pre-condition: none
// Post-condition: All memory returned.
//
concordance::~concordance() {
	Node* tmp;
	while (first != NULL) {
		tmp = first;
		first = first->next;
		delete tmp;
	}
}

// operator<<
//
// writes the list of word-count pairs to the `out_s` stream.
//
// Pre-condition: A concordance `s`.
// Post-condition: That concordance written to `out_s`.
ostream& operator<<(ostream &out_s, const concordance &s) {
	concordance::Node* p = s.first;
	out_s << "-------------------\n";
	out_s << "|Word        Count|\n";
	out_s << "|-----------------|\n";
	while (p != NULL) {
		cout << '|' << left << setw(8) << p->word << "|";
		cout << right << setw(8) << p->count << "|\n";
		p = p->next;
	}
	out_s << "-------------------\n";
	return out_s;
}

bool less_than(const char a[], const char b[]) {
	return r_less_than(a, b, 0);
}

bool r_less_than(const char a[], const char b[], int i) {
	if (a[i] == '\0' && b[i] == '\0')
		return false;
	if (b[i] == '\0')
		return false;
	if (a[i] == '\0')
		return true;
	if (a[i] < b[i])
		return true;
	if (a[i] == b[i])
		return r_less_than(a, b, i + 1);

	return false;
}

bool equals(const char a[], const char b[]) {
	return r_equals(a, b, 0);
}

bool r_equals(const char a[], const char b[], int i) {
	if (a[i] == '\0' && b[i] == '\0')
		return true;
	if (b[i] == '\0')
		return false;
	if (a[i] == '\0')
		return false;
	if (a[i] == b[i])
		return r_equals(a, b, i + 1);

	return false;
}
