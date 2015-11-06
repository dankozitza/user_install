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

typedef Q<int> Teller;

template <class T>
T min(T v1, T v2, T v3);

template <class T>
T cstrton(char* str);

int main(int argc, char* argv[]) {
   int time = 0;
   int cust_id = 77;
   int servers;        // Number of queue/server pairs.
   int cust_prob;      // Probablility that a customer will arive in one tick.
   int max_trans_time; // Maximum amount of time for a single transaction.
   int sim_duration;   // Amount of time to run for.
   int seed;           // Seed to be used to generate random number.

   if (argc == 6) {
      servers = atoi(argv[1]);
      cust_prob = atoi(argv[2]);
      max_trans_time = atoi(argv[3]);
      sim_duration = atoi(argv[4]);
      seed = atoi(argv[5]);
   }
   else {
      cout << "\nYou need to enter the variables used during the simulation.\n";
      cout << "These values can also be entered as command line arguments.\n";
      cout << "   ex: " << argv[0];
      cout << " QS_PAIRS CUST_PROB MAX_TRANS_TIME SIM_DURATION SEED\n\n";
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
   }

   srand(seed);
   Teller *staff = new Teller[servers];

   for (time; time <= sim_duration; ++time) {

      cout << "\nclock: " << time << endl;

      if (cust_prob > rand() % 100) {
         int r_teller = rand() % servers;
         staff[r_teller].enq(cust_id++);
      }
   
      for (int i = 0; i < servers; ++i) {
         cout << "   teller: " << right << setw(3) << i + 1;
         cout << left << "   - wait time: ";
         cout << right << setw(3) << "F";
         cout << left << "   - line: " << staff[i] << "\n";
      }
      cout << endl;
   }

   delete []staff;
   return 0;
}

template <class T>
T min (T v1, T v2, T v3) {
   if (v1 <= v2 && v1 <= v3)
      return v1;
   if (v2 <= v1 && v2 <= v3)
      return v2;

   return v3;
}
