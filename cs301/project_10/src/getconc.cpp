//
// getconc.cpp
//
// This program takes one filename as a command line argument and prints
// a list of all the words found in it along with the number of times that
// word appears.
//
// Project 10
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 11/25/2015
//

#include <iostream>
#include <fstream>
#include "concordance.hpp"

using namespace std;

void testconc();

int main(int argc, char *argv[]) {
   ifstream ifs;
   concordance::Word word;
   concordance conc;
   char c;
   size_t w_size = 0;

   if (argc != 2) {
      cout << "USAGE: " << argv[0] << " FILE\n";
      return 0;
   }

   // for testing concordance::get_count and concordance::length
   if (argv[1][0] == 'Z') {
      testconc();
      return 0;
   }

   ifs.open(argv[1]);
   if (!ifs.is_open()) {
      cout << "could not open file " << argv[1] << endl;
      return 0;
   }

   ifs.get(c);
   while(ifs.good()) {
      // convert upper case letters to lower case
      if ('A' <= c && c <= 'Z')
         c += 32;

      if ('a' <= c && c <= 'z') {
         if (w_size < WORD_CAP - 1) {
            word[w_size++] = c;
            word[w_size] = '\0';
         }
      }
      else if (w_size > 0) {
         conc.insert(word);
         w_size = 0;
         word[0] = '\0';
      }

      ifs.get(c);
   }
   // in case the last character in the file is a letter
   if (w_size > 0)
      conc.insert(word);

   cout << conc;
   return 0;
}

void testconc() {
   concordance conc;
   cout << "---- Test Mode Activated  ----\n";
   concordance::Word wrd = {'h', 'h', 'h', '\0', '\0', '\0', '\0', '\0'};
   cout << "Word wrd = `" << wrd << "`\n";
   cout << "length(): `" << conc.length() << "`\n";
   cout << "get_count(wrd): `" << conc.get_count(wrd) << "`\n";
   cout << "calling: `conc.insert(wrd);`\n";
   conc.insert(wrd);
   cout << "length(): `" << conc.length() << "`\n";
   cout << "get_count(wrd): `" << conc.get_count(wrd) << "`\n";
   cout << "calling: `conc.insert(wrd);`\n";
   conc.insert(wrd);
   cout << "length(): `" << conc.length() << "`\n";
   cout << "get_count(wrd): `" << conc.get_count(wrd) << "`\n";
}
