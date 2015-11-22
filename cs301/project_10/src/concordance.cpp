//
// concordance.cpp
//
// ADT that uses a binary search tree. Each Node in the tree has a word, a
// count (the number of times that word has been inserted), and pointers to
// it's child Nodes.
//
// Project 10
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 11/25/2015
//

#include "concordance.hpp"
#include <cstring>
#include <iomanip>

concordance::concordance() {
   root = NULL;
   size = 0;
}

concordance::~concordance() {
   destroy(root);
}

// insert
//
// Inserts `word` into the list in it's appropriate place alphabetically.
//
// Pre-condition: A word.
// Post-condition: That word inserted into the list.
//
void concordance::insert(Word word) {
   Node *p = root, *back = NULL;
   int ret;

   while (p != NULL) {
      back = p;
      ret = strcmp(word, p->word);
      if (ret < 0) {
         p = p->left;
      }
      else if (ret > 0) {
         p = p->right;
      }
      else {
         p->count++;
         return;
      }
   }

   if (back == NULL)
      root = get_node(word, NULL, NULL);
   else if (ret < 0)
      back->left = get_node(word, NULL, NULL);
   else
      back->right = get_node(word, NULL, NULL);
   size++;
}

// get_count
//
// Returns the number of times `word` appears.
//
// Pre-condition: A word.
// Post-condition: Returns the count for that word.
//
long concordance::get_count(Word word) {
   Node *p = root;
   int ret;
   while (p != NULL) {
      ret = strcmp(word, p->word);
      if (ret < 0)
         p = p->left;
      else if (ret > 0)
         p = p->right;
      else
         return p->count;
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
   return size;
}


// operator<<
//
// writes the list of word-count pairs to the `out_s` stream.
//
// Pre-condition: A concordance `s`.
// Post-condition: That concordance written to `out_s`.
ostream& operator<<(ostream &out_s, concordance &conc) {
   out_s << "Word        Count\n";
   out_s << "-----------------\n";
   conc.r_print(conc.root, out_s);
   return out_s;
}

// get_node
//
// Tool used to create a new node.
//
// Pre-condition: a word w, it's count, and a pointer to next.
// Post-condition: returns a pointer to a new node.
//
concordance::Node* concordance::get_node(Word w, Node *left, Node *right) {
   Node* tmp = new Node;
   for (int i = 0; i < WORD_CAP; i++)
      tmp->word[i] = w[i];
   tmp->count = 1;
   tmp->left  = left;
   tmp->right = right;
   return tmp;
}

// destroy
//
// Deletes each node in the tree pointed at by p.
//
void concordance::destroy(Node *p) {
   if (p != NULL) {
      destroy(p->left);
      destroy(p->right);
      delete p;
   }
}

// r_print
//
// recursively prints the data in order.
//
void concordance::r_print(Node *p, ostream &out_s) {
   if (p != NULL) {
      r_print(p->left, out_s);
      out_s << left << setw(8) << p->word;
      out_s << right << setw(8) << p->count << "\n";
      r_print(p->right, out_s);
   }
}
