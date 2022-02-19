//
// Student Name: HoldenG
// Date: 03/01/2019
// Course:  Data Structures
// Assignment:  HW# 03 - Create a job queue simulation
//

#ifndef DATASTRUCT_HW03_SIM_H
#define DATASTRUCT_HW03_SIM_H

#include <vector>
#include "VM.h"
#include "MyQueue.h"
#include <chrono>
#include <random>

#define Q_EVENT_FILE "C:\\Users\\-\\CLionProjects\\DataStruct-HW03\\QueueSequence.csv"
#define DONE_QUEUE_FILE "C:\\Users\\-\\CLionProjects\\DataStruct-HW03\\Done_Queue.txt"

#define           MACHINES  4           // The number of virtual machines to create
#define   CPUS_PER_MACHINE  16          // The number of CPUs in each VM

#define REQUESTED_NUM_JOBS  10000       // The number of jobs to simulate

#define MIN_ARRIV_DELAY_ns   1000       // The MIN arrival delay
#define MAX_ARRIV_DELAY_ns 100000       // The MAX arrival delay

#define MIN_JOB_LEN_ns       4000       // The MIN job length
#define MAX_JOB_LEN_ns    4000000       // The MIN job length

#define TIME_NOW chrono::system_clock::now()   // A constant definition to make checking the time easier

using namespace std;

class Sim {

public:


    Sim();                                              // Simulation Constructor
    vector<VM> VMs;                                     // Vector to hold virtual machine objects
    MyQueue<Job> runQueue;                              // Queue object to hold jobs ready to run
    MyQueue<Job> doneQueue;                             // Queue object to hold jobs completed

    void runSimulation(int totJobsNeeded);              // Main simulation routine
    void runSimulation();                               // Overridden method to use #define value

    chrono::system_clock::time_point getMaxQTm();       // Chrono timepoint of when queue max size happened
    chrono::system_clock::time_point getSimStartTm();   // Chrono timepoint of when the simulation started
    int getMaxQLeng() const;
    void calcSimulStats();                              // Function to calculate final simulation statistics
    void printSimulStats();                             // Function to print final simulation statistics
    void printStats();                                  // Function to print stats
    void printMaxEvent();                               // Function to print the max queue length stats
    void doneQtoFile();                                 // Function to write the done queue to a file

private:
    ofstream Q_EventFile ;
    int maxQLeng;                                       // Most elements ever in queue at one time
    int runQueueLength;                                 // Length of queue
    int requestedJobs;                                  // Number of jobs being simulated
    int currJobNum;                                     // Number of jobs made
    bool arrived();                                     // Function to check for simulated job arrival
    void checkForJob();                                 // Function to see if more jobs are needed
    void testQLeng();                                   // Function to test for maximum queue size
    chrono::system_clock::time_point maxQTm;            // Time Max size happened
    chrono::system_clock::time_point simStartTm;        // Time simulation began
    chrono::system_clock::time_point nextArriveTm;      // Time to simulate next arrival

    chrono::nanoseconds totalJobWaitTm{0};              // Total wait time of job
    chrono::nanoseconds totalJobTurnTm{0};              // Total turn around time of job
    chrono::nanoseconds totalJobRunTm{0};               // Total run time of job
    chrono::microseconds avgJobWaitTm{0};               // Average wait time of all jobs
    chrono::microseconds avgJobTurnTm{0};               // Average turn around time of all jobs
    chrono::microseconds avgJobRunTm{0};                // Average run time of all jobs
    chrono::microseconds maxJobRun{0};                  // Longest length of all job run times
    chrono::microseconds minJobRun{0};                  // Shortest length of all job run times


};


#endif //DATASTRUCT_HW03_SIM_H
