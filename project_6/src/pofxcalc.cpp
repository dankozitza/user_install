//
// pofxcalc.cpp
//
// This program is a calculator that reads arithmetic expressions from a file
// using postfix notation.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

#include <fstream>
#include <iostream>
//#include "Stack.hpp"

using namespace std;

class calc {
   private:
      Stack::Value value;
      Stack stack;

   public:
      // clears stack, reads istream and sets value
      istream& operator>>(istream& is, calc& c); 
      ostream& operator<<(ostream& os, calc& c);
}

istream& calc::operator>>(istream& is, calc& c) {
   char c, last = ' ';
   int cnt = 0;

   v.clear();

   is.get(c);
   while (c != '\n') {

      if (c != ' ' && c != '   ') {

         if (v.empty() || v.size() == cnt)
            // beginning of new token

         // TODO: decide what to use to hold a token before it's value is
         // determined
         v[cnt] += c;
      }
      else if (last != ' ' && last != '	') {
         // if c is a space but last is not then the word is done
         cnt++;
      }

      last = c;
      is.get(c);
   }

   return is;
}

int main(int argc, char *argv[]) {
   calc c;
   ifstream ifs;

   if (argc != 2) {
      cout << "USAGE: " << argv[0] << " FILE\n";
      return 0;
   }

   ifs.open(argv[1]);
   if (!ifs.is_open()) {
      cout << "could not open file `" << argv[1] << "`\n";
      return 0;
   }

   while (ifs.peek() != EOF) {
      ifs >> c;
      cout << c;
   }

   ifs.close();
   return 0;
}
