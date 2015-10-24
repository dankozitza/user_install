//
// Infxcalc.cpp
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

#include "Infxcalc.hpp"

Infxcalc::Infxcalc() {
   expression_cnt = 0;
   valid = false;
   expr = new char[EXPR_CAP];
}

Infxcalc::~Infxcalc() {
   delete expr;
}

// evaluate
//
//
//
bool Infxcalc::evaluate(char* expr, int start = 0) {
   Token token, next_t;
   char last_c = ' ';
   bool done = false, token_pair_ready = false;
   int tsize = 0, ntsize = 0;

   bool kk

   optr_stack.clear();
   opnd_stack.clear();
   valid = false;

   token[0] = '\0';
   next_t[0] = '\0';

   for (int i = start; !done; ++i) {

      // ignore spaces and tabs
      if (expr[i] != ' ' && expr[i] != '	') {

         if (tsize < TOKEN_CAP - 1) {
            next_t[ntsize++] = c;
            next_t[ntsize] = '\0';
         }
         else {
            cerr << "Infxcalc: In expresion `" << expr;
            cerr << "`: Token `" << token << "` excedes token capacity.\n";
            return false;
         }
      }
      else if (last != ' ' && last != '	') {
         // if c is a space but last is not then next_t is done
         if (token[0] == '\0')
            strcpy(token, next_t);
         else
            token_pair_ready = true;
      }

      while (token_pair_ready) {
         // if we can apply what's on the stacks do it
         if (optr_stack.size() == opnd_stack.size() - 1
               && precedes(optr_stack.peek(), next_t)) {
         }
         // otherwise place token in the stack and collect the next token
         else {

            // handle the token (place it in it's appropriate stack)

            strcpy(token, next_t)

            // break
            token_pair_ready = false;
         }
      }

      last_c = expr[i];
   } // end of loop
}

// evaluate
//
// Adds a token to the expression. If the token is an operand it applies the
// operand to it's operators. If the token is an operator it stores the value
// for later use.
//
// Returns false if an error is encountered. True otherwise.
//
// Pre-condition: a token
// Post-condition: that token evaluated
//
bool Infxcalc::evaluate(Token token) {
   bool negative = false;
   valid = false;

   // handle the negative numbers
   if (token[0] == '-' && token[1] >= '0' && token[1] <= '9') {
      negative = true;
      token[0] = '0';
   }

   if (token[0] >= '0' && token[0] <= '9') {
      // token is a digit
      Number n = 0;
      // convert token to integer
      for (int i = 0; token[i] != '\0'; i++) {
         if (!(token[i] >= '0' && token[i] <= '9')) {
            cerr << "Infxcalc: In expression " << expression_cnt << ": ";
            cerr << "'" << token << "' is not a valid operand.\n";
            return false;
         }
         n = n * 10 + (token[i] - '0');
      }

      if (negative)
         n = n * -1;

      stack.push(n);
   }
   else if (token[1] != '\0') {
      // invalid token
      cerr << "Infxcalc: In expression " << expression_cnt << ": ";
      cerr << "'" << token << "' is not a valid operator.\n";
   }
   else if (token[0] == '+') {
      // do operation
      if (stack.size() < 2) {
         cerr << "Infxcalc: In expression " << expression_cnt << ": ";
         cerr << "Not enough operands for operator '" << token << "'.\n";
         return false;
      }

      stack.push(stack.pop() + stack.pop());

      if (stack.size() == 1) {
         valid = true;
      }
   }
   else if (token[0] == '-') {
      // do operation
      if (stack.size() < 2) {
         cerr << "Infxcalc: In expression " << expression_cnt << ": ";
         cerr << "Not enough operands for operator '" << token << "'.\n";
         return false;
      }

      Number right_val = stack.pop();
      stack.push(stack.pop() - right_val);

      if (stack.size() == 1) {
         valid = true;
      }
   }
   else if (token[0] == '*') {
      // do operation
      if (stack.size() < 2) {
         cerr << "Infxcalc: In expression " << expression_cnt << ": ";
         cerr << "Not enough operands for operator '" << token << "'.\n";
         return false;
      }

      stack.push(stack.pop() * stack.pop());


      if (stack.size() == 1) {
         valid = true;
      }
   }
   else if (token[0] == '/') {
      // do operation
      if (stack.size() < 2) {
         cerr << "Infxcalc: In expression " << expression_cnt << ": ";
         cerr << "Not enough operands for operator '" << token << "'.\n";
         return false;
      }

      Number right_val = stack.pop();
      stack.push(stack.pop() / right_val);

      if (stack.size() == 1) {
         valid = true;
      }
   }
   else {
      cerr << "Infxcalc: In expression " << expression_cnt << ": '";
      cerr << token << "' is not a valid operator.\n";
      return false;
   }

   return true;
}
