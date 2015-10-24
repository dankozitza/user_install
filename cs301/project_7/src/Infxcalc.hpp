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
#include "C_Stack.hpp"
#include "N_Stack.hpp"

using namespace std;

const size_t TOKEN_CAP = 10;

class Infxcalc {
   private:
      typedef char Token[TOKEN_CAP];
      typedef long Number;
      C_Stack optr_stack;
      N_Stack opnd_stack;
      bool valid;

      
      bool apply();
      bool is_operator(Token t);
      bool place(Token token);
      bool precedes(char c1, char c2);

   public:

      Infxcalc();
      bool evaluate(char* expr, char delim);
      bool evaluate(char* expr, int& start, char delim);
      Number result();
};

#endif
