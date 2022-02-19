//
// Student Name: HoldenG
// Date: 03/01/2019
// Course:  Data Structures
// Assignment:  HW# 03 - Create a job queue simulation
//

#include "CPU.h"

#include <iostream>
#include <chrono>

using namespace std;

// Initialize a new CPU object with the identifiers passed to it
CPU::CPU(int VMnum, int CPUnum) {
    this->totJobs = 0;                              // Initialize total jobs run on CPU to 0
    this->totRunTm = chrono::nanoseconds{0};        // Init total Run time of CPU to 0
    this->CPUstartTm = chrono::system_clock::now(); // Init CPU start time to creation time
    this->VM_Id = VMnum + 1;                        // Assign CPU's Virtual Machine ID
    this->CPU_Id = CPUnum + 1;                      // Assign CPU's CPU ID
    this->runningJob = nullptr;                     // Point running job address to NULL
    setReady(true);                                 // Set CPU Ready to True
}

// Assign job to run on CPU
void CPU::setCurrJobOnCPU(Job *currJob) {
    this->runningJob = currJob;             // Set running job pointer to passed job object
    this->totJobs++;                        // Increment number of jobs CPU has processed
    this->setRunStartTm();                  // Set CPU run start time
    this->getRunningJob()->setJobStartTm();             // Set run start time on Job
    this->getRunningJob()->setOnVM(this->getVMid());    // Set Virtual Machine ID on Job
    this->getRunningJob()->setOnCPU(this->getCPUid());  // Set CPU ID on Job
    setReady(false);                                    // Set CPU to Busy
}

// Test (Current time - run start) to determine if assigned job length has passed
bool CPU::jobIsFinished() {
    return (chrono::nanoseconds{chrono::system_clock::now() - this->runStartTm}
            > (getRunningJob()->getJobAssignedLeng()));
}

// Remove current job from CPU and return address of job object that just completed
Job* CPU::removeCurrJobFromCPU() {
    Job* temp = getRunningJob();            // Store address of data object to return
    this->getRunningJob()->setJobEndTm();   // Timespamp End time of job
    this->setRunEndTm();                    // Timestamp CPU run end time
    this->totRunTm += (chrono::nanoseconds{         // Add the CPU run time of this job
        (this->runEndTm) - (this->runStartTm)});    // to total running time of CPU
    this->lastEndTm = chrono::system_clock::now();  // Timestamp most recent run end
    this->runningJob = nullptr;         // Set CPUs current job to NULL
    setReady(true);                     // Set CPU to ready
    return temp;                        // Return object address to be moved to done queue
}

void CPU::setReady(bool ready) {
    this->ready = ready;
}

void CPU::setRunStartTm() {
    this->runStartTm = chrono::system_clock::now();
}

void CPU::setRunEndTm() {
    CPU::runEndTm = chrono::system_clock::now();
}

chrono::system_clock::time_point CPU::getRunStartTm() const {
    return runStartTm;
}
chrono::system_clock::time_point CPU::getRunEndTm() const {
    return runEndTm;
}

chrono::nanoseconds CPU::getTotRunTm() const {
    return totRunTm;
}

bool CPU::isReady() {
    return this->ready;
}

Job* CPU::getRunningJob() const {
    return runningJob;
}
int CPU::getTotJobs() const {
    return totJobs;
}





void CPU::printCPUstats() {
    cout << "\n===================================================================\n\n";
    cout << "     ****  VM " << getVMid() << " - CPU " << getCPUid() << "  ****"<< endl;
    cout << "    Total Jobs Served: " << this->totJobs << endl;
    cout << "Total Processing Time: " << chrono::duration_cast<chrono::microseconds>
            (this->totRunTm).count()<< " us" << endl;
    cout << "      Total Idle Time: " << chrono::duration_cast<chrono::microseconds>
            ((this->lastEndTm)-(this->CPUstartTm) - (this->totRunTm)).count()<< " us" << endl << endl;
    cout << "Started at: " << chrono::duration_cast<chrono::microseconds>
            (this->CPUstartTm.time_since_epoch()).count() << " microseconds since epoch " << endl << endl;
}



int CPU::getVMid() const {
    return VM_Id;
}

int CPU::getCPUid() const {
    return CPU_Id;
}
