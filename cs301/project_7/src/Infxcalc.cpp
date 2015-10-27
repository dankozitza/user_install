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
   valid = false;
}

// evaluate
//
// Takes a character array `expr`, optional integer reference `i`, and
// delimiter `delim`. The array is read one character at a time starting at i
// and ending at delim. by default i is set to 0 and delim is set to \0.
//
// Return:
//    true  - The expression was evaluated successfully. result function can
//            be called.
//    false - The expression is invalid. calling result function will cause
//            error.
//
bool Infxcalc::evaluate(const char* expr) {
   return evaluate(expr, '\0');
}
bool Infxcalc::evaluate(const char* expr, char delim) {
   int tmp = 0;
   return evaluate(expr, tmp, delim);
}
bool Infxcalc::evaluate(const char* expr, int& i, char delim) {
   Token token;
   char last_c = ' ';
   bool done = false, token_ready = false;
   int tsize = 0;

   optr_stack.clear();
   opnd_stack.clear();
   valid = false;

   token[0] = '\0';

   // loop through each character in expr including final \0
   for (i; !done; ++i) {

      // make recursive call then push resulting number onto opnd_stack
      if (last_c == ' ' && expr[i] == '(') {
         Infxcalc r_calc;
         if (!r_calc.evaluate(expr, ++i, ')')) {
            return false;
         }

         opnd_stack.push(r_calc.result());
         if (opnd_stack.size() == 1 && optr_stack.size() == 0)
            valid = true;
         last_c = ' ';
      }

      // check for end of token and collect characters into token array
      if (expr[i] == delim) {
         done = true;
         if (token[0] != '\0')
            if (!place(token))
               return false;
      }
      else if (expr[i] == '\0' || expr[i] == ')') {
         cerr << "Infxcalc: found delimiter '" << expr[i] << "' when ";
         cerr << "expecting delimiter '" << delim << "'\n";
         return false;
      }
      else if (expr[i] == ' ' && last_c != ' ') {
         token_ready = true;
      }
      else if (expr[i] != ' ') {

         if (tsize < TOKEN_CAP - 1) {
            token[tsize++] = expr[i];
            token[tsize] = '\0';
         }
         else {
            cerr << "Infxcalc: In expresion `" << expr;
            cerr << "`: Token `" << token << "` excedes token capacity.\n";
            return false;
         }
      }

      // apply if we can
      if (done) {
         while (apply()) {};
      }
      else if (token_ready) {
         token_ready = false;

         while (is_operator(token)
               && optr_stack.size() > 0
               && precedes(optr_stack.peek_c(), token[0])
               && apply()) {}

         if (!place(token))
            return false;

         token[0] = '\0';
         tsize = 0;
      }

      last_c = expr[i];
   }

   return valid;
}

// result
//
// Returns result of the expression.
//
Infxcalc::Number Infxcalc::result() {
   assert(valid);
   assert(opnd_stack.size() == 1 && optr_stack.size() == 0);
   return opnd_stack.peek_l();
}

// is_operator
//
// Returns true if the token is an operator.
//
bool Infxcalc::is_operator(Token t) {
   if (t[1] == '\0') {
      switch (t[0]) {
         case '+':
         case '-':
         case '*':
         case '/':
            return true;
      }
   }
   return false;
}
 
// place
// 
// Pushes a token onto the operator stack or the operand stack. When a token
// is added to a stack the expression is no longer valid. Apply must be called
// and perform a successful operation for the expression to become valid again.
//
// Return:
//    true  - The token was valid and placed on the appropriate stack.
//    false - The token was invalid.
//
bool Infxcalc::place(Token token) {
   bool negative = false;

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
            cerr << "Infxcalc::place: ";
            cerr << "'" << token << "' is not a valid operand.\n";
            return false;
         }
         n = n * 10 + (token[i] - '0');
      }

      if (negative)
         n = n * -1;

      valid = false;
      opnd_stack.push(n);
   }
   else if (is_operator(token)) {
      valid = false;
      optr_stack.push(token[0]);
   }
   else {
      // invalid token
      cerr << "Infxcalc::place: '" << token << "' is not a valid operator.\n";
      return false;
   }

   return true;
}

// precedes
//
// Returns true if c1 precedes c2 in order of operations.
//
bool Infxcalc::precedes(char c1, char c2) {
   return (!(c1 == '+' || c1 == '-') && (c2 == '*' || c2 == '/'));
}

// apply
//
// Applies the top operator in optr_stack to the two top operands in opnd_stack.
// The valid member is set to true by this function when an operation is applied
// successfully AND there is a single item left on the operand stack.
//
// Return:
//    true  - An operation was applied successfully.
//    false - No operation was applied.
//
bool Infxcalc::apply() {
   Number right_opnd;
   char optr;

   if (optr_stack.size() >= 1
         && optr_stack.size() == opnd_stack.size() - 1) {
      optr = optr_stack.pop_c();
      right_opnd = opnd_stack.pop_l();

      cout << "applying " << opnd_stack.peek_l() << " " << optr << " " << right_opnd << endl;

      switch (optr) {
         case '+':
            opnd_stack.push(opnd_stack.pop_l() + right_opnd);
            if (opnd_stack.size() == 1)
               valid = true;
            break;
         case '-':
            opnd_stack.push(opnd_stack.pop_l() - right_opnd);
            if (opnd_stack.size() == 1)
               valid = true;
            break;
         case '*':
            opnd_stack.push(opnd_stack.pop_l() * right_opnd);
            if (opnd_stack.size() == 1)
               valid = true;
            break;
         case '/':
            opnd_stack.push(opnd_stack.pop_l() / right_opnd);
            if (opnd_stack.size() == 1)
               valid = true;
            break;
         default:
            // place ensures all operators in the stack are valid
            cerr << "Infxcalc::apply: invalid operator '" << optr << "'\n";
            assert(false);
      }
      return true;
   }
   return false;
}
