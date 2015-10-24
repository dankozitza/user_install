//
// infixcalc.cpp
//
// This program is a calculator that reads arithmetic expressions from a file
// using infix notation. Each line of the file is considered one expression.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

#include <fstream>
#include <iostream>
#include "Infxcalc.hpp"

using namespace std;

const size_t STR_CAP = 5;

void append(char* &str, int& size, int& dyn_cap, char new_c);

int main(int argc, char *argv[]) {
   Infxcalc calc;
   ifstream ifs;
   char c;
   int str_cap = STR_CAP;
   char *expression = new char[str_cap];
   int esize = 0;

   if (argc != 2) {
      cout << "USAGE: " << argv[0] << " FILE\n";
      return 0;
   }

   ifs.open(argv[1]);
   if (!ifs.is_open()) {
      cout << "infixcalc: Could not open file `" << argv[1] << "`.\n";
      return 0;
   }

   ifs.get(c);
   while (ifs.good()) {

      if (c != '\n') {
         append(expression, esize, str_cap, c);
      }
      else {
         cout << "Expression: `" << expression << "`\n";
         if (calc.evaluate(expression, '\0'))
            cout << "Result: `" << calc.result() << "`\n\n";
         else
            cout << "Result: invalid expression\n\n";

         expression[0] = '\0';
         esize = 0;
      }
      
      ifs.get(c);
   }

   if (ifs.bad()) {
      cerr << "infixcalc: I/O error while reading file: `";
      cerr << argv[1] << "`\n";
   }

   ifs.close();
   return 0;
}

void append(char* &str, int& size, int& dyn_cap, char new_c) {
   if (size >= dyn_cap - 1) {
      cout << "append: size: " << size << "\n";
      cout << "append: dyn_cap + STR_CAP: " << dyn_cap + STR_CAP << "\n";
      dyn_cap += STR_CAP;
      cout << "append: dyn_cap: " << dyn_cap << "\n";
      char* tmp = new char[dyn_cap];
      for (int i = 0; i <= size; ++i)
         tmp[i] = str[i];

      delete []str;
      str = tmp;
   }

   str[size++] = new_c;
   str[size] = '\0';
}
