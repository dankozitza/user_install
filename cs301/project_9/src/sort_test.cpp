//
// sort_test.cpp
//
// This program is used to compare different sorting algorithms. Each sorting
// function will be called. The 'count' variable the functions return tells the
// number of characteristic operations done during the sort.
//
// Project 9
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 11/16/2015
//

#include <cstdlib>
#include <iostream>
#include "sorters.hpp"

using namespace std;

typedef int Value;

void help();

int main(int argc, char* argv[]) {
   Value *fuzz1, *fuzz2, *fuzz3; // Arrays of random values to be sorted.
   size_t f_size = 0;            // Size of the fuzz array.
   int seed = 0;                 // Seed to be used to generate random number.
   int rand_cap = 100;           // Capacity for numbers generated as values.
   bool quiet = false;
   bool increment = false;
   bool decrement = false;
   unsigned long long count;

   for (int i = 1; i < argc; ++i) {
      if (argv[i][0] == '-') {
         switch (argv[i][1]) {
            case 'q':
               quiet = true;
               break;
            case 'i':
               decrement = false;
               increment = true;
               break;
            case 'd':
               increment = false;
               decrement = true;
               break;
            case 'n':
               f_size = atoi(argv[i++ + 1]);
               break;
            case 's':
               seed = atoi(argv[i++ + 1]);
               break;
            case 'c':
               rand_cap = atoi(argv[i++ + 1]);
               break;
            case 'h':
               help();
               return 0;
            default:
               cout << "sort_test: unknown argument: `" << argv[i] << "`.\n";
               help();
               return 0;
         }
      }
      else {
         cout << "sort_test: unknown argument: `" << argv[i] << "`. ";
         cout << "Try \"" << argv[0] << " -h\"\n";
         return 0;
      }
   }

   while (f_size <= 0) {
      cout << "Enter the number of generated values: ";
      cin >> f_size;
   }
   if (seed == 0 && !increment && !decrement) {
      cout << "Enter a random integer: ";
      cin >> seed;
   }

   fuzz1 = new Value[f_size];
   fuzz2 = new Value[f_size];
   fuzz3 = new Value[f_size];

   if (increment) {
      for (int i = 0; i < f_size; ++i)
         fuzz1[i] = i;
   }
   else if (decrement) {
      for (int i = 0; i < f_size; ++i)
         fuzz1[i] = f_size - 1 - i;
   }
   else {
      srand(seed);
      for (int i = 0; i < f_size; ++i)
         fuzz1[i] = rand() % rand_cap;
   }

   // coppy values
   for (int i = 0; i < f_size; ++i) {
      fuzz2[i] = fuzz1[i];
      fuzz3[i] = fuzz1[i];
   }

   if (!quiet) {
      cout << "Fuzz array before being sorted:\n   ";
      for (int i = 0; i < f_size - 1; ++i)
         cout << fuzz1[i] << " ";
      cout << fuzz1[f_size - 1] << "\n";
   }

   count = sorters::insert<Value, size_t, unsigned long long>(fuzz1, f_size);

   if (!quiet) {
      cout << "\nArray after insert sort:\n   ";
      for (int i = 0; i < f_size - 1; ++i)
         cout << fuzz1[i] << " ";
      cout << fuzz1[f_size - 1] << "\n";
   }

   cout << "Insert Sort count: " << count << endl;

   count = sorters::merge<Value, size_t, unsigned long long>(fuzz2, f_size);

   if (!quiet) {
      cout << "\nArray after merge sort:\n   ";
      for (int i = 0; i < f_size - 1; ++i)
         cout << fuzz2[i] << " ";
      cout << fuzz2[f_size - 1] << "\n";
   }

   cout << "Merge Sort count: " << count << endl;

   count = sorters::quick<Value, size_t, unsigned long long>(fuzz3, f_size);

   if (!quiet) {
      cout << "\nArray after quick sort:\n   ";
      for (int i = 0; i < f_size - 1; ++i)
         cout << fuzz3[i] << " ";
      cout << fuzz3[f_size - 1] << "\n";
   }
   cout << "Quick Sort count: " << count << "\n\n";

   delete []fuzz1;
   delete []fuzz2;
   delete []fuzz3;
   return 0;
}

void help() {
   cout << "\nsort_test is a program used to compare sorting algorithms.\n\n";
   cout << "Usage:\n\n   ";
   cout << "sort_test [-q] [-i] [-d] [-n i] [-s i] [-c i]\n\n";
   cout << "Arguments:\n\n";
   cout << "   -q      Turns quiet mode on. ";
   cout << "Only the final counts will be printed.\n";
   cout << "   -i      Generated values will increment.\n";
   cout << "   -d      Generated Values will decrement.\n";
   cout << "   -n i    Sets the number of values generated to i.\n";
   cout << "   -s i    Sets the random seed to i. Ignored if -i or -d options ";
   cout << "are given.\n";
   cout << "   -c i    Sets the maximum random number allowed to i - 1. ";
   cout << "Ignored\n           if -i or -d options are given.\n\n";
}
