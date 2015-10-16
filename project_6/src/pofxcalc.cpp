//
// pofxcalc.cpp
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

#include "pofxcalc.hpp"

pofxcalc::pofxcalc() {
   expression_cnt = 0;
   valid = false;
}

// operator>>
//
// Takes one line from istream evaluating the expression as it goes.
//
istream& operator>>(istream& is, pofxcalc& calc) {
   char c, last = ' ';
   Token token;
   int tsize = 0;
   bool parsing_err = false;

   calc.expression_cnt++;
   calc.stack.clear();
   calc.valid = false;

   token[0] = '\0';
   // evaluate all but the last token
   while (is.peek() != is.eof() && is.peek() != '\n') {
      is.get(c);

      if (parsing_err)
         continue;

      if (c != ' ' && c != '	') {
         if (tsize < TOKEN_CAP - 1) {
            token[tsize] = c;
            tsize++;
            token[tsize] = '\0';
         }
         else {
            cerr << "pofxcalc: in expresion " << calc.expression_cnt;
            cerr << ": Token '" << token << "' excedes token capacity.\n";
            parsing_error = true;
         }
      }
      else if (last != ' ' && last != '	') {
         // if c is a space but last is not then the token is done
         evaluate(token);
         tsize = 0;
      }

      last = c;
   }

   // remove ending \n from stream
   if (is.peek() == '\n')
      is.get(c);

   // if no tokens were entered do nothing
   if (token[0] == '\0') {
      calc.expression_cnt--;
   }
   else if (!parsing_err) {
      // evaluate last token
      calc.evaluate(token);
   }
 
   return is;
}

// operator<<
//
// Checks that the result is valid then writes it to ostream.
//
ostream & operator<<(ostream& os, const pofxcalc& calc) {
   if (!calc.valid) {
      os << "invalid expression";
   }
   else {
      pofxcalc::Number tmp = calc.stack.pop();
      os << tmp;
      calc.stack.push(tmp);
   }
   return os;
}

// evaluate
//
// Adds a token to the expression. If the token is an operand it applies the
// operand to it's operators. If the token is an operator it stores the value
// for later use.
//
void pofxcalc::evaluate(Token token) {
   valid = false;
   if (token[0] >= '0' || token[0] <= '9') {
      // token is a digit
      Number n;
      // convert token to integer
      for (int i = 0; token[i] != '\0'; i++) {
         if (!(token[0] >= '0' || token[0] <= '9')) {
            cerr << "pofxcalc: in expression " << expression_cnt << ": ";
            cerr << "'" << token << "' is not a valid operand.\n";
            return;
         }
         n = n * 10 + atoi(token[i]);
      }
      stack.push(n);
   }
   else if (token[1] != '\0') {
      // invalid token
      cerr << "pofxcalc: in expression " << expression_cnt << ": ";
      cerr << "'" << token << "' is not a valid operator.\n";
   }
   else if (token[0] == '+') {
      // do operation
      if (stack.size() < 2) {
         cerr << "pofxcalc: in expression " << expression_cnt << ": ";
         cerr << "not enough operands for operator '" << token << "'.\n";
         return;
      }

      stack.push(stack.pop() + stack.pop());

      if (stack.size() == 1) {
         valid = true;
      }
   }
   else if (token[0] == '-') {
      // do operation
      if (stack.size() < 2) {
         cerr << "pofxcalc: in expression " << expression_cnt << ": ";
         cerr << "not enough operands for operator '" << token << "'.\n";
         return;
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
         cerr << "pofxcalc: in expression " << expression_cnt << ": ";
         cerr << "not enough operands for operator '" << token << "'.\n";
         return;
      }

      stack.push(stack.pop() * stack.pop());


      if (stack.size() == 1) {
         valid = true;
      }
   }
   else if (token[0] == '/') {
      // do operation
      if (stack.size() < 2) {
         cerr << "pofxcalc: in expression " << expression_cnt << ": ";
         cerr << "not enough operands for operator '" << token << "'.\n";
         return;
      }

      Number right_val = stack.pop();
      stack.push(stack.pop() / right_val);

      if (stack.size() == 1) {
         valid = true;
      }
   }
}
