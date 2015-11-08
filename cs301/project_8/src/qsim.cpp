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
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Q.hpp"

using namespace std;

struct Customer {
   int  id;
   int  arrival_time;
   int* time;
};

struct Teller {
   Q<Customer> line;
   int         wait;
   Customer    customer;
};

void print(int time, int staff_size, int cst_prob, int max_trans_time,
           int sim_duration, int seed, Teller staff[]);
int mins(Teller a[], int a_size, int lows[]);
ostream& operator<<(ostream& out, const Customer& cstmr);

int main(int argc, char* argv[]) {
   int time = 0;
   int cust_id = 1;
   int customers_served = 0;
   int average_wait = 0;
   int longest_wait = 0;
   int staff_size;     // Number of queue/server pairs.
   int cst_prob;       // Probablility that a customer will arive in one tick.
   int max_trans_time; // Maximum amount of time for a single transaction.
   int sim_duration;   // Amount of time to run for.
   int seed;           // Seed to be used to generate random number.
   bool quiet = false;

   int arg_start = 1;
   if (argc >= 2 && strcmp(argv[1], "-q") == 0) {
      quiet = true;
      arg_start = 2;
   }
   if ((argc == 6 && !quiet) || (argc == 7 && quiet)) {
      staff_size = atoi(argv[arg_start++]);
      cst_prob = atoi(argv[arg_start++]);
      max_trans_time = atoi(argv[arg_start++]);
      sim_duration = atoi(argv[arg_start++]);
      seed = atoi(argv[arg_start]);
   }
   else if ((argc == 1 && !quiet) || (argc == 2 && quiet)) {
      cout << "\nYou need to enter the variables used during the simulation.\n";
      cout << "These values can also be entered as command line arguments.\n";
      cout << "   ex: " << argv[0];
      cout << " QS_PAIRS CUST_PROB MAX_TRANS_TIME SIM_DURATION SEED\n\n";
      cout << "A customer will be represented as an 'id|wait_time' pair.\n";
      cout << "   ex: customer 12 who's been waiting 30 minutes would be\n";
      cout << "       represented as '12|30'.\n\n";
      cout << "Enter the number of queue/server pairs: ";
      cin >> staff_size;
      cout << "Enter the customer arrival probability (0 - 100): ";
      cin >> cst_prob;
      cout << "Enter the maximum transaction time (minutes): ";
      cin >> max_trans_time;
      cout << "Enter the simulation duration time (minutes): ";
      cin >> sim_duration;
      cout << "Enter a random integer: ";
      cin >> seed;
      cout << endl;
   }
   else {
      cout << "USAGE: " << argv[0];
      cout << " [-q] [QS_PAIRS CUST_PROB MAX_TRANS_TIME SIM_DURATION SEED]\n";
      return 0;
   }

   srand(seed);
   Teller *staff = new Teller[staff_size];

   for (time; time < sim_duration; ++time) {

      if (cst_prob > rand() % 100) {

         // check for available tellers
         int at_size = 0;
         int *available_tellers = new int[staff_size];
         for (int teller = 0; teller < staff_size; ++teller)
            if (staff[teller].customer.id == 0)
               available_tellers[at_size++] = teller;

         // a teller is ready to serve the customer
         if (at_size > 0) {
            int rat = available_tellers[rand() % at_size];
            Customer cstmr = {cust_id++, time, &time};
            staff[rat].customer = cstmr;
            staff[rat].wait = rand() % max_trans_time + 1;
         }
         // the customer needs to get into the shortest line
         else {
            // mins places the indexes of the tellers with the lowest and equal
            // line sizes into the lows array.
            int *lows = new int[staff_size];
            int l_size = mins(staff, staff_size, lows);

            // randomly pick a teller index from the array mins gives.
            int r_teller = lows[rand() % l_size];
            delete []lows;

            // place a new customer in the line.
            Customer cstmr = {cust_id++, time, &time};
            staff[r_teller].line.enq(cstmr);
         }
         delete available_tellers;
      }

      if (!quiet)
         print(time, staff_size, cst_prob, max_trans_time,
               sim_duration, seed, staff);

      // serve customers
      for (int i = 0; i < staff_size; ++i) {
         if (staff[i].customer.id != 0) {
            --staff[i].wait;

            if (staff[i].wait == 0) {
               customers_served++;

               int total_wait = time - staff[i].customer.arrival_time + 1;
               if (average_wait > 0)
                  average_wait = (average_wait + total_wait) / 2;
               else
                  average_wait = total_wait;

               if (longest_wait < total_wait)
                  longest_wait = total_wait;

               Customer cstmr = {0, 0, 0};
               staff[i].customer = cstmr;

               if (staff[i].line.size() > 0) {
                  staff[i].customer = staff[i].line.deq();
                  staff[i].wait = rand() % max_trans_time + 1;
               }
            }
         }
      }
   }

   if (!quiet)
      print(time, staff_size, cst_prob, max_trans_time,
            sim_duration, seed, staff);

   int in_line = 0;
   for (int k = 0; k < staff_size; ++k)
      in_line += staff[k].line.size();

   cout << "Total customers served: " << customers_served << endl;
   cout << "Average customer wait time: " << average_wait << endl;
   cout << "Longest customer wait time: " << longest_wait << endl;
   cout << "Customers still in line: " << in_line << endl;

   delete []staff;
   return 0;
}

void print(int time, int staff_size, int cst_prob, int max_trans_time,
           int sim_duration, int seed, Teller staff[]) {
   cout << "clock: " << time << " staff_size: " << staff_size;
   cout << " cst_prob: " << cst_prob;
   cout << " max_trans_time: " << max_trans_time;
   cout << " sim_duration: " << sim_duration;
   cout << " seed: " << seed << endl;
   cout << "teller   wait time   serving      line\n";
   for (int i = 0; i < staff_size; ++i) {
      cout << right << setw(4) << i + 1;
      cout << left << " ";
      cout << right << setw(9) << staff[i].wait;
      if (staff[i].customer.id == 0)
         cout << "           ";
      else
         cout << "       " << staff[i].customer;
      cout << left << "    " << staff[i].line << "\n";
   }
   cout << endl;
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
int mins(Teller a[], int a_size, int lows[]) {
   int l_size = 0;
   if (a_size < 1)
      return 0;
   int lowest = a[0].line.size();
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

ostream& operator<<(ostream& out, const Customer& cstmr) {
   out << right << setw(4) << cstmr.id << "|";
   out << left << setw(3) << *cstmr.time - cstmr.arrival_time;
   return out;
}
