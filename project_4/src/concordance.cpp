//
// concordance.cpp
//
// ADT that stores an ordered linked list of Nodes. Each Node has an item (in
// this case a word), a count (the number of times that item has been inserted),
// and a pointer to the next Node.
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
	Node* p = first;
	Node* pre = p;
	if (first == NULL || less_than(word, first->word)) {
		first = get_node(word, 1, first);
		return;
	}
	if (equals(word, first->word)) {
		first->count++;
		return;
	}

	while (p != NULL) {
		cout << "comparing " << word << " and " << p->word << endl;
		if (less_than(word, p->word)) {
			cout << word << " is less than " << p->word << endl;
			pre->next = get_node(word, 1, pre->next);
			return;
		}
		cout << "--- before equals with " << word << " and " << p->word << endl;
		if (equals(word, p->word)) {
			cout << word << " equals " << p->word << endl;
			p->count++;
			return;
		}
		cout << word << " is greater than " << p->word << endl;
		pre = p;
		p = p->next;
	}

	// if word is the last alphabetically
	cout << "it's last\n";
	pre->next = get_node(word, 1, NULL);
}

int concordance::get_count(const Word &word) {
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

