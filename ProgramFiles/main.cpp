//
// Student Name: HoldenG
// Date: 03/05/2019
// Course:  Data Structures
// Assignment:  HW# 03 - Create a job queue simulation
//

// This program simulates jobs which are of random assigned lengths
// and have random delays between their arrival. All time values are
// actual time values using <chrono> at sub-millisecond units.
//
// The Simulation object creates a vector of Virtual Machine objects, each
// one containing a vector of CPU objects.
//
// The simulation also creates a Run Queue object for jobs that need to be
// processed, and a Completed Queue object for jobs that are done. Both are
// custom Template Linked Lists that hold Job objects.
//
// For each CPU of each VM, tests the following logic is performed:
// - Test if a new job has "arrived" based on time comparison against
// delay. If it has:
// Create the job object, stamp time, place it into the Run Queue, and
// increase Run Queue length. Write information about the queue event to
// Queue Event CSV file (including the size of the queue) - for import
// into Excel to visualize time and queue size with scatterplot diagram.
// Also test to see if the new job is the smallest or biggest so far.
//
// - Test if the current CPU has a job and is done processing it (elapsed
// time on cpu is longer than assigned length). If so, stamp time and move
// job to Completed Queue. Also, if the final job was just moved to
// completed queue, set simulation Done flag to true.
//
// - Test if the current processor is ready and there is a job available
// in the Run Queue. If so, stamp time, move job from Run Queue to the CPU,
// and decrease Run Queue length. Write information about the queue event to
// CSV file (including the new size of the queue).
//
// - If the simulation is not done, move to next Machine/CPU

#include <iostream>
#include "MyQueue.h"
#include "Job.h"
#include "Sim.h"
#include <random>
#include <ctime>



using namespace std;


int main() {
    srand(time(nullptr));

    try {

        Sim simul = Sim();
        simul.runSimulation( );

        // Print completed jobs
        if ( !(simul.doneQueue.isEmpty())) {
            simul.doneQtoFile();
            simul.printStats();
        }
        else { cout << "No Jobs Were Completed\n";}

    } catch (exception const &ex) {
        cout.flush();
        cout << "\n\n ********* EXCEPTION: " << ex.what() << endl << endl;
        cerr << "EXCEPTION: " << ex.what() << endl;
        return -1;
    }

    return 0;
}



