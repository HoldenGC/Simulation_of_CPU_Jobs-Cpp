//
// Student Name: HoldenG
// Date: 03/01/2019
// Course:  Data Structures
// Assignment:  HW# 03 - Create a job queue simulation
//

#ifndef DATASTRUCT_HW03_JOB_H
#define DATASTRUCT_HW03_JOB_H

#include <chrono>
#include <fstream>

using namespace std;

class Job {

private:
    int jobID;                                      // ID number of Job - sequential integers
    int onCPU;                                      // ID of CPU job ran on
    int onVM;                                       // ID number of Virtual Machine ran on
    chrono::nanoseconds assignedLen;                // Random length assigned to job
    chrono::system_clock::time_point jobStartTm;    // Timestamp of job start time on CPU
    chrono::system_clock::time_point jobEndTm;      // Timestamp of job end time
    chrono::system_clock::time_point jobArrivalTm;  // Timestamp of when job arrived at Run Queue

public:
    Job(int jobID, long );
    void filePrintJob(ofstream &JobstatOut);         // File print entire completed queue
    chrono::system_clock::time_point getJobArrivalTm();
    chrono::system_clock::time_point getJobStartTm() const;
    chrono::system_clock::time_point getJobEndTm() const;
    chrono::nanoseconds getJobWaitTm();
    chrono::nanoseconds getJobRunTm();
    chrono::nanoseconds getJobTurnTm();
    chrono::nanoseconds getJobAssignedLeng() const;
    int getJobID();
    void setJobStartTm();
    void setJobEndTm();
    int getOnCPU() const;
    int getOnVM() const;
    void setOnCPU(int onCPU);
    void setOnVM(int onVM);

};


#endif //DATASTRUCT_HW03_JOB_H
