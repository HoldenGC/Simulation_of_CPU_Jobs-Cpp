//
// Student Name: HoldenG
// Date: 03/01/2019
// Course:  Data Structures
// Assignment:  HW# 03 - Create a job queue simulation
//
#ifndef DATASTRUCT_HW03_CPU_H
#define DATASTRUCT_HW03_CPU_H

#include "Job.h"
#include <string>
using namespace std;

class CPU {

public:
    CPU(int VMnum, int CPUnum);

    int getVMid() const;
    int getCPUid() const;
    bool isReady();
    void setReady(bool ready);

    Job* getRunningJob() const;
    void setCurrJobOnCPU(Job *currJob);
    Job* removeCurrJobFromCPU();

    int getTotJobs() const;

    chrono::system_clock::time_point  getRunStartTm() const;
    chrono::system_clock::time_point  getRunEndTm() const;
    chrono::nanoseconds getTotRunTm() const;

    void setRunStartTm();
    void setRunEndTm();

    bool jobIsFinished();
    void printCPUstats();

private:
    int VM_Id;
    int CPU_Id;
    int totJobs;
    bool ready;
    Job* runningJob;

    chrono::system_clock::time_point CPUstartTm;
    chrono::system_clock::time_point runStartTm;
    chrono::system_clock::time_point runEndTm;
    chrono::system_clock::time_point lastEndTm;

    chrono::nanoseconds totRunTm;

};


#endif //DATASTRUCT_HW03_CPU_H
