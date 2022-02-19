//
// Student Name: HoldenG
// Date: 03/01/2019
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

#include "Sim.h"
#include "Job.h"
#include <stdio.h>
/////////////////////////////////////////////////////
//             CONSTRUCTORS & GETTERS
/////////////////////////////////////////////////////
// Simulation object constructor creates Vector of Virtual Machines and opens Queue Event file
Sim::Sim() {
    runQueueLength = 0;                             // Initialize size of queue
    currJobNum = 0;                                 // Initialize number of jobs
    for (int i =0; i < MACHINES; i++){              // For each machine,
        VMs.push_back(*new VM(i,CPUS_PER_MACHINE)); // Create needed number of CPU objects
    }
    this->Q_EventFile.open(Q_EVENT_FILE);
}

void Sim::runSimulation() {                         // Overloaded constructor for use when number of jobs
    this->runSimulation(REQUESTED_NUM_JOBS);        // value is not passed and #define value will be used
}
chrono::system_clock::time_point Sim::getSimStartTm() {     // Start time of simulation
    return simStartTm;
}
int Sim::getMaxQLeng() const {                              // Max num of elements in Queue at once
    return maxQLeng;
}
chrono::system_clock::time_point Sim::getMaxQTm() {         // Time the Max number of elements happened
    return maxQTm;
}

/////////////////////////////////////////////////////
//            SIMULATION PROCESS
/////////////////////////////////////////////////////
// MAIN SIMULATION FUNCTION - See program description
void Sim::runSimulation(int totJobsNeeded) {
    simStartTm = TIME_NOW;           // Set start time
    maxQTm = TIME_NOW;               // Initialize max time
    nextArriveTm = simStartTm + chrono::nanoseconds{    // Create first simulated arrival time
            (std::rand() % (MAX_ARRIV_DELAY_ns - MIN_ARRIV_DELAY_ns + 1)) + MIN_ARRIV_DELAY_ns};
    // Print completed queue header to file, include the simulation start time
    Q_EventFile << "toQueue, toCPU, Job_ID, Q_Size, Time_Epoch_uS, START:, " << chrono::duration_cast<chrono::microseconds>
            (this->simStartTm.time_since_epoch()).count() << endl;
    this->requestedJobs = totJobsNeeded;                // Set number of jobs to simulate
    bool finished = false;                              // Initialize simulation complete flag

    while (!finished){                                  // Until the simulation is completed
        for (VM& mach : this->VMs){                     // Cycle through each machine
            for (CPU& proc : mach.CPUs) {               // Cycle through each CPU on each machine
                checkForJob();                          // Check for job arrival
                if (!(proc.isReady()) && proc.jobIsFinished()){    // If the CPU has been running job and finished
                    doneQueue.enqueue(*proc.removeCurrJobFromCPU());   // Move job from CPU into the completed queue
                    if (doneQueue.getLength() == requestedJobs) // If all needed jobs have been moved to done queue
                    { finished = true;}                     // Set simulation completed flag to true
                }
                if (proc.isReady() && !(runQueue.isEmpty())) {  // If the CPU is ready and there are jobs in queue
                                                                // Write to Queue Event CSV file
                    Q_EventFile << "0, 1, " << runQueue.getFront().getJobID() << ", " << this->runQueueLength -1 << ", "
                            << chrono::duration_cast<chrono::microseconds>(TIME_NOW.time_since_epoch()).count() << endl;
                    proc.setCurrJobOnCPU(&runQueue.dequeue());  // Move job from front of run queue to CPU
                    runQueueLength--;                           // Decrease size of queue
                }
            }
        }
    }
    this->Q_EventFile.close();
}

// Check for simulated arrival of job
bool Sim::arrived() {       // Check current time for greater then next requested job start time
    if (TIME_NOW > nextArriveTm) {
        nextArriveTm += chrono::nanoseconds{    // If true, Increase next planned arrival time & indicate arrival
                (std::rand() % (MAX_ARRIV_DELAY_ns - MIN_ARRIV_DELAY_ns + 1)) + MIN_ARRIV_DELAY_ns};
        return true;
    } else return false;
}

// Check if there are still jobs to simulate and it is time for one to arrive
void Sim::checkForJob() {
    if ((this->currJobNum < this->requestedJobs) && arrived()){
        runQueue.enqueue(*new Job(++(this->currJobNum),(std::rand() % (MAX_JOB_LEN_ns
             - MIN_JOB_LEN_ns +1)) + MIN_JOB_LEN_ns));     // Create new job and place on back of run queue
        this->runQueueLength++;                                        // Increment job counter
        Q_EventFile << "1, 0, " << runQueue.getRear().getJobID() << ", " << this->runQueueLength << ", "
                << chrono::duration_cast<chrono::microseconds>(TIME_NOW.time_since_epoch()).count() << endl;
        testQLeng();                                            // Check for new max length
    }
}
// Check for run queue length greater than ever before.
void Sim::testQLeng() {
    if (runQueueLength > maxQLeng) {                   // If queue is longest ever,
        maxQLeng = runQueueLength;                     // Set max length to current length
        maxQTm = TIME_NOW;                             // Set the time of maximum length to now
    }
}
/////////////////////////////////////////////////////
//            SIMULATION STATS CALCULATIONS
/////////////////////////////////////////////////////
// Cycle through completed queue, cumulate values, find max and min run time, and calculate averages
void Sim::calcSimulStats() {
    // Initialize accumulators
    this->totalJobWaitTm = chrono::nanoseconds{0};
    this->totalJobRunTm = chrono::nanoseconds{0};
    this->totalJobTurnTm = chrono::nanoseconds{0};

    // Attempt to move to start of the list, and if successful, continue into loop
    if (this->doneQueue.firstElem()) {
        // Move through completed queue and accumulate needed values
        do {
            this->totalJobWaitTm += this->doneQueue.currElem().getJobWaitTm();
            this->totalJobRunTm += this->doneQueue.currElem().getJobRunTm();
            this->totalJobTurnTm += this->doneQueue.currElem().getJobTurnTm();
            // Check for longest actual job run length
            if (this->doneQueue.currElem().getJobRunTm() > this->maxJobRun){
                this->maxJobRun = chrono::duration_cast<chrono::microseconds>
                        (doneQueue.currElem().getJobRunTm() );
            } else
                // Check for shortest actual job run length
            if ((this->doneQueue.currElem().getJobRunTm() < this->minJobRun) || (this->minJobRun.count() < 1 )){
                this->minJobRun = chrono::duration_cast<chrono::microseconds>
                        (doneQueue.currElem().getJobRunTm() );
            }
        } while (this->doneQueue.nextElem());

        // Calculate average values by dividing accumulators by the number of jobs run
        avgJobWaitTm = chrono::duration_cast<chrono::microseconds>
                (totalJobWaitTm / doneQueue.getLength());
        avgJobTurnTm = chrono::duration_cast<chrono::microseconds>
                (totalJobTurnTm / doneQueue.getLength());
        avgJobRunTm = chrono::duration_cast<chrono::microseconds>
                (totalJobRunTm / doneQueue.getLength());

    }
}
/////////////////////////////////////////////////////
//   WRITE COMPLETED QUEUE TO FILE & PRINT STATS
/////////////////////////////////////////////////////

// Print entire completed Queue to Done Queue File
void Sim::doneQtoFile(){
        ofstream DoneQueueOut;
        DoneQueueOut.open(DONE_QUEUE_FILE);
        if (this->doneQueue.firstElem()) {
            do {
                this->doneQueue.currElem().filePrintJob(DoneQueueOut);
            } while (this->doneQueue.nextElem());
        }
        DoneQueueOut.close();
};
// Print CPU Statistics, simulation statistics, and Max queue length event
void Sim::printStats() {
    cout << "\n===================================================================\n\n";
    cout << "                    MACHINE CONFIGURATION\n";
    cout << "                    ---------------------\n\n";
    cout << "                 NUMBER OF VIRTUAL MACHINES: " << MACHINES << endl;
    cout << "           NUMBER OF CPUS PER VIRTUAL MACHINE: " << CPUS_PER_MACHINE << endl;
    cout << "                 TOTAL NUMBER OF CPUS USED: " << CPUS_PER_MACHINE * MACHINES << endl << endl;
    cout << "                NUMBER OF JOBS SIMULATED: " << REQUESTED_NUM_JOBS << endl << endl;
    cout << "               - RANDOM LIMITS (MICROSECONDS) -" << endl;
    printf("      MIN DELAY:%10d        MIN RUN REQUEST:%10d\n", MIN_ARRIV_DELAY_ns / 1000, MIN_JOB_LEN_ns / 1000);
    printf("      MAX DELAY:%10d        MAX RUN REQUEST:%10d\n", MAX_ARRIV_DELAY_ns / 1000, MAX_JOB_LEN_ns / 1000);
    cout << "\n===================================================================\n\n";
    cout << "                        CPU STATISTICS\n";
    cout << "                        --------------\n";

    for (VM &mach : this->VMs) {
        for (CPU &proc : mach.CPUs) {
            proc.printCPUstats();
        }
    }

    cout << "\n===================================================================\n\n";
    cout << "                    SIMULATION STATISTICS\n";
    cout << "                    ---------------------\n";

    this->printSimulStats();

    cout << "\n===================================================================\n\n";
    cout << "                 MAXIMUM QUEUE LENGTH EVENT\n";
    cout << "                 --------------------------\n";

    this->printMaxEvent();
    cout << endl << endl;
}

void Sim::printSimulStats() {
    calcSimulStats();
    cout << "\n===================================================================\n\n";
    cout << "           Total Number of jobs processed: " << doneQueue.getLength() << endl;
    cout << "       Average Run Time of jobs processed: "
         << (chrono::duration_cast<chrono::microseconds>(this->avgJobRunTm)).count() << " microseconds" << endl;
    cout << "      Average Wait Time of jobs processed: " <<
         (chrono::duration_cast<chrono::microseconds>(this->avgJobWaitTm)).count()  << " microseconds" << endl;
    cout << "Average Turnaround Time of jobs processed: " <<
         (chrono::duration_cast<chrono::microseconds>(this->avgJobTurnTm)).count()  << " microseconds" <<endl << endl;

    cout << "           Minimum job run time processed: " <<
         (chrono::duration_cast<chrono::microseconds>(this->minJobRun)).count() << " microseconds" << endl;
    cout << "           Maximum job run time processed: " <<
         (chrono::duration_cast<chrono::microseconds>(this->maxJobRun)).count() << " microseconds" << endl;
}

// Print Maximum lenth of run queue and time when it happened
void Sim::printMaxEvent() {
    cout << "\n===================================================================\n\n";
    cout << "Max number of jobs in queue at one time: " << this->getMaxQLeng() << endl;
    cout << "Happened at: " << chrono::duration_cast<chrono::microseconds>(this->getMaxQTm().time_since_epoch()).count()
         << " us since Epoch\n";
    cout << "Or " << chrono::duration_cast<chrono::microseconds>(this->getMaxQTm() - this->getSimStartTm()).count()
         << " microseconds after simulation start\n";
    cout << "\n===================================================================" << endl;
}



