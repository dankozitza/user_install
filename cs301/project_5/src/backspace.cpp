//
// backspace.cpp
//
// Program that takes a string of characters as input treating the # character
// as if it were a backspace. Outputs the string with deleted and # characters
// removed
//
// Project 5
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 10/12/2015
//

#include <iostream>
#include "d_list.hpp"

using namespace std;

int main() {
   d_list dl;
   char c;

   cout << "enter string: ";

   cin.get(c);
   while (c != '\n') {

      if (c != '#')
         dl.append(c);
      else
         dl.remove_last();

      cin.get(c);
   }

   cout << dl << endl;

   return 0;
}
