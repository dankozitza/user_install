//
// pofxcalc.hpp
//
// Calculator that reads arithmetic expressions from a file using postfix
// notation. Each line of the file is considered one expression.
//
// Project 6
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/21/2015
//

#ifndef _POFXCALC
#define _POFXCALC

#include <iostream>
#include "Stack.hpp"

using namespace std;

// this may need to be 9. a long int cannot hold all 10 digit numbers
const size_t TOKEN_CAP = 10;
const size_t EXPR_CAP = 100;

class pofxcalc {
   private:
      typedef char Token[TOKEN_CAP];
      typedef long int Number;
      Stack stack;
      int expression_cnt;
      bool valid;
      char* expr;

      bool evaluate(Token token);

   public:

      pofxcalc();
      ~pofxcalc();
      char* expression();

      friend istream& operator>>(istream& is, pofxcalc& c); 
      friend ostream& operator<<(ostream& os, pofxcalc& c);
};

#endif
