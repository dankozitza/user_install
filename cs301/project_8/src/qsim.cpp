//
// qsim.cpp
//
// This program simulates queues.
//
// Project 8
// Created by Daniel Kozitza
// account number cs301145
// CSCI 301 section 2
// Due 11/09/2015
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Q.hpp"

using namespace std;

struct Teller {
   Q<int> line;
   int    wait;
   int    customer;
};

size_t mins(Teller a[], size_t a_size, size_t lows[]);

int main(int argc, char* argv[]) {
   int time = 0;
   int cust_id = 77;
   int staff_size;     // Number of queue/server pairs.
   int cust_prob;      // Probablility that a customer will arive in one tick.
   int max_trans_time; // Maximum amount of time for a single transaction.
   int sim_duration;   // Amount of time to run for.
   int seed;           // Seed to be used to generate random number.

   if (argc == 6) {
      staff_size = atoi(argv[1]);
      cust_prob = atoi(argv[2]);
      max_trans_time = atoi(argv[3]);
      sim_duration = atoi(argv[4]);
      seed = atoi(argv[5]);
   }
   else if (argc == 1) {
      cout << "\nYou need to enter the variables used during the simulation.\n";
      cout << "These values can also be entered as command line arguments.\n";
      cout << "   ex: " << argv[0];
      cout << " QS_PAIRS CUST_PROB MAX_TRANS_TIME SIM_DURATION SEED\n\n";
      cout << "Enter the number of queue/server pairs: ";
      cin >> staff_size;
      cout << "Enter the customer arrival probability (1 - 100): ";
      cin >> cust_prob;
      cout << "Enter the maximum transaction time (minutes): ";
      cin >> max_trans_time;
      cout << "Enter the simulation duration time (minutes): ";
      cin >> sim_duration;
      cout << "Enter a random integer: ";
      cin >> seed;
   }
   else {
      cout << "USAGE: " << argv[0];
      cout << " [QS_PAIRS CUST_PROB MAX_TRANS_TIME SIM_DURATION SEED]\n";
      return 0;
   }

   srand(seed);
   Teller *staff = new Teller[staff_size];

   for (time; time <= sim_duration; ++time) {

      cout << "\nclock: " << time << endl;
      cout << "teller   wait time   line\n";
      for (int i = 0; i < staff_size; ++i) {
         cout << right << setw(4) << i + 1;
         cout << left << " ";
         cout << right << setw(9) << staff[i].wait;
         cout << left << "         " << staff[i].line << "\n";
      }
      cout << endl;

      if (cust_prob > rand() % 100) {

         // mins places the indexes of the tellers with the lowest and equal
         // line sizes into the lows array.
         size_t *lows = new size_t[staff_size];
         size_t l_size = mins(staff, staff_size, lows);

         // randomly pick a teller index from the array mins gives.
         int r_teller = lows[rand() % l_size];
         delete []lows;
         staff[r_teller].line.enq(cust_id++);

         // randomly generate a wait time for tellers without one.
         if (staff[r_teller].line.size() == 1)
            staff[r_teller].wait = rand() % max_trans_time + 1;
      }

      for (int i = 0; i < staff_size; ++i) {

         if (staff[i].line.size() > 0) {
           
            if (staff[i].wait == 0) {
               cout << "staff[" << i << "].deq(): ";
               cout << staff[i].line.deq() << endl;

               if (staff[i].line.size() > 0)
                  staff[i].wait = rand() % max_trans_time + 1;
            }
            else {
               --staff[i].wait;
            }
         }
      }

   }

   delete []staff;
   return 0;
}

// mins
//
// Used to select randomly from the shortest lines when enqueueing a new
// customer.
//
// Parameters:
//    a        - The array of tellers.
//    a_size   - The size of the array of tellers.
//    lows     - An array of equal size that will be populated with the indexes
//               of the shortest lines in a.
//
// Return value:
//    The size of the lows array.
//
size_t mins(Teller a[], size_t a_size, size_t lows[]) {
   size_t l_size = 0;
   if (a_size < 1)
      return 0;
   size_t lowest = a[0].line.size();
   lows[l_size++] = 0;

   for (int i = 1; i < a_size; ++i) {
      if (lowest == a[i].line.size()) {
         lows[l_size++] = i;
      }
      else if (lowest > a[i].line.size()) {
         lowest = a[i].line.size();
         l_size = 0;
         lows[l_size++] = i;
      }
   }
   return l_size;
}
