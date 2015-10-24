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

bool Infxcalc::evaluate(char* expr, char delim = '\0') {
   int tmp = 0;
   return evaluate(expr, tmp, delim);
}

// evaluate
//
//
//
bool Infxcalc::evaluate(char* expr, int& start, char delim = '\0') {
   Token token;
   char last_c = ' ';
   bool done = false, token_ready = false;
   int tsize = 0;

   optr_stack.clear();
   opnd_stack.clear();
   valid = false;

   token[0] = '\0';

   // looping through each character in expr including final \0
   for (int i = start; !done; ++i) {

      //if (last_c == ' ' && expr[i] == '(') {
      //   // make recursive call then place resulting token or convert
      //   // into token and set token_ready

      //   cout << "\ngot here. i: " << i << "\n\n";
      //   Infxcalc r_calc;
      //   int r_i = i;
      //   if (!r_calc.evaluate(expr, r_i, ')')) {
      //      cerr << "Infxcalc::evaluate: could not evaluate subexpression!\n";
      //      return false;
      //   }
      //   cout << "\ngot here 2. i: " << r_i << "\n\n";
      //
      //   //opnd_stack.push(r_calc.result());
      //   last_c = ' ';
      //   continue;
      //}

      // check for end of token and collect characters into token array
      if (expr[i] == delim) {
         done = true;
         if (token[0] != '\0')
            token_ready = true;
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

      //cout << "expr[" << i << "]: `" << expr[i] << "` token: `" << token << "`\n";

      if (done) {
         cout << "done, applying\n";
         if (token_ready)
            if (!place(token))
               return false;
         while (apply()) {};
      }
      else if (token_ready) {
         token_ready = false;

         //cout << "not done, token " << token << " is ready!\n";

         //cout << "Not done! applying\n";
         while (is_operator(token)
               && precedes(optr_stack.peek(), token[0])
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
   if (valid) {
      return opnd_stack.peek();
   }
   else {
      return 0;
   }
}

bool Infxcalc::is_operator(Token t) {
   if (t[1] == '\0') {
      switch (t[0]) {
         case '+':
         case '-':
         case '*':
         case '/':
            return true;
            break;
      }
   }
   return false;
}
 
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

      opnd_stack.push(n);
   }
   else if (is_operator(token)) {
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
// Returns true if c1 precedes c2 in order of operations. False otherwise.
//
bool Infxcalc::precedes(char c1, char c2) {
   switch (c1) {
      case '+':
      case '-':
         switch (c2) {
            case '*':
            case '/':
               return false;
            default: // c2 is either + or -
               return true;
         }
      default: // c1 is either * or /
         return true;
   }
}

// apply
//
// applies the top operator in optr_stack to the two top operands in opnd_stack.
//
bool Infxcalc::apply() {
   Number right_opnd;
   char optr;

   if (optr_stack.size() >= 1
         && optr_stack.size() == opnd_stack.size() - 1) {
      optr = optr_stack.pop();
      right_opnd = opnd_stack.pop();

      //cout << "applying " << optr << " to " << opnd_stack.peek() << " and ";
      //cout << right_opnd << "\n";

      switch (optr) {
         case '+':
            opnd_stack.push(opnd_stack.pop() + right_opnd);
            if (opnd_stack.size() == 1)
               valid = true;
            break;
         case '-':
            opnd_stack.push(opnd_stack.pop() - right_opnd);
            if (opnd_stack.size() == 1)
               valid = true;
            break;
         case '*':
            opnd_stack.push(opnd_stack.pop() * right_opnd);
            if (opnd_stack.size() == 1)
               valid = true;
            break;
         case '/':
            opnd_stack.push(opnd_stack.pop() / right_opnd);
            if (opnd_stack.size() == 1)
               valid = true;
            break;
         default:
            cerr << "Infxcalc::apply: '" << optr;
            cerr << " is not a valid operation\n";
            valid = false;
            return false;
      }
      return true;
   }
   else {
      return false;
   }
}
