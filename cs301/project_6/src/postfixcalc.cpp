//
// postfixcalc.cpp
//
// This program is a calculator that reads arithmetic expressions from a file
// using postfix notation. Each line of the file is considered one expression.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

#include <fstream>
#include <iostream>
#include "Pofxcalc.hpp"

using namespace std;

int main(int argc, char *argv[]) {
   Pofxcalc calc;
   ifstream ifs;

   if (argc != 2) {
      cout << "USAGE: " << argv[0] << " FILE\n";
      return 0;
   }

   ifs.open(argv[1]);
   if (!ifs.is_open()) {
      cout << "postfixcalc: Could not open file `" << argv[1] << "`.\n";
      return 0;
   }

   while (ifs >> calc) {
      cout << "Expression: `" << calc.expression() << "`\n";
      cout << "Result: `" << calc << "`\n\n";
   }

   if (ifs.bad()) {
      cerr << "postfixcalc: I/O error while reading file: `";
      cerr << argv[1] << "`\n";
   }

   ifs.close();
   return 0;
}
