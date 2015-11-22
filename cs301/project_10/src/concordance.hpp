//
// concordance.hpp
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

#ifndef _CONCORDANCE
#define _CONCORDANCE

#include <iostream>

using namespace std;

const size_t WORD_CAP = 9;

class concordance {

   public:
      typedef char Word[WORD_CAP];

      concordance();
      ~concordance();
      void   insert(Word word);
      long   get_count(Word word);
      size_t length();
      friend ostream& operator<<(ostream &out_s, concordance &s);

   private:
      struct Node {
         Word word;
         long count;
         Node *left;
         Node *right;
      };

      Node  *root;
      size_t size;

      Node* get_node(Word w, Node *left, Node *right);
      void  destroy(Node *p);
      void  r_print(Node *p, ostream &out_s);
};

#endif
