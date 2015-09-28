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
	cout << "it's last\n";
	pre->next = get_node(word, 1, NULL);
}

int concordance::get_count(Word word) {
	Node* p = first;
	while(p != NULL) {
		if (equals(p->word, word))
			return p->count;
		p = p->next;
	}
	return 0;
}

size_t concordance::length() {
}

concordance::~concordance() {
}

concordance::Node* concordance::get_node(Word w, int cnt, Node* p) {
	Node* tmp = new Node;
	for (int i = 0; i < WORD_CAP; i++)
		tmp->word[i] = w[i];
	tmp->count = cnt;
	tmp->next = p;
	return tmp;
}

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
