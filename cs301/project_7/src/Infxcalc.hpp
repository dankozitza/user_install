//
// Infxcalc.hpp
//
// Calculator that reads arithmetic expressions from a file using infix
// notation. Each line of the file is considered one expression.
//
// Project 7
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/30/2015
//

#ifndef _POFXCALC
#define _POFXCALC

#include <iostream>
#include "Stack.hpp"

using namespace std;

const size_t TOKEN_CAP = 10;

class Infxcalc {
   private:
      typedef char Token[TOKEN_CAP];
      typedef long Number;
      C_stack optr_stack;
      N_stack opnd_stack;
      bool valid;

   public:

      Infxcalc();
      bool apply();
      bool evaluate(char* expr, int start);
      bool precedes(Token t1, Token t2);
      bool place(Token t);
};

#endif
