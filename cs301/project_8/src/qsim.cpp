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
#include "Q.hpp"

using namespace std;

typedef Q<int> Teller;

int main() {
   int time = 0;
   int cust_id = 77;
   int servers;        // Number of queue/server pairs.
   int cust_prob;      // Probablility that a customer will arive in one tick.
   int max_trans_time; // Maximum amount of time for a single transaction.
   int sim_duration;   // Amount of time to run for.
   int seed;           // Seed to be used to generate random number.

   cout << "Enter the number of queue/server pairs: ";
   cin >> servers;
   cout << "Enter the customer arrival probability (1 - 100): ";
   cin >> cust_prob;
   cout << "Enter the maximum transaction time (minutes): ";
   cin >> max_trans_time;
   cout << "Enter the simulation duration time (minutes): ";
   cin >> sim_duration;
   cout << "Enter a random integer: ";
   cin >> seed;

   Teller *staff = new Teller[servers];

   for (time; time < sim_duration; ++time) {

      if (cust_prob > rand() % 100) {
         int r_teller = rand() % servers;
         staff[r_teller].enq(cust_id++);
      }
   
      for (int i = 0; i < servers; ++i)
         cout << "teller " << i + 1 << ": " << staff[i] << "\n";
      cout << endl;
   }

   return 0;
}
