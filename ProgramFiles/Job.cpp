//
// Student Name: HoldenG
// Date: 03/01/2019
// Course:  Data Structures
// Assignment:  HW# 03 - Create a job queue simulation
//

#include "Job.h"
#include <random>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;



Job::Job(int jobID, long randomLength){
    this->jobID = jobID;
    this->assignedLen = chrono::nanoseconds {randomLength};
    this->jobArrivalTm = chrono::system_clock::now();
}

int Job::getJobID(){
    return this->jobID;
}

chrono::nanoseconds Job::getJobAssignedLeng() const {
    return assignedLen;
}
chrono::system_clock::time_point Job::getJobStartTm() const {
    return jobStartTm;
}
void Job::setJobStartTm() {
    Job::jobStartTm =  chrono::system_clock::now();
}
chrono::system_clock::time_point Job::getJobEndTm() const {
    return jobEndTm;
}
void Job::setJobEndTm() {
    Job::jobEndTm =  chrono::system_clock::now();
}

int Job::getOnCPU() const {
    return onCPU;
}

int Job::getOnVM() const {
    return onVM;
}

void Job::setOnCPU(int onCPU) {
    Job::onCPU = onCPU;
}

void Job::setOnVM(int onVM) {
    Job::onVM = onVM;
}

chrono::system_clock::time_point Job::getJobArrivalTm() {
    return jobArrivalTm;
}

chrono::nanoseconds Job::getJobWaitTm() {
    return (this->getJobStartTm() - this->getJobArrivalTm());
}

chrono::nanoseconds Job::getJobRunTm() {
    return (this->getJobEndTm() - this->getJobStartTm());
}
chrono::nanoseconds Job::getJobTurnTm() {
    return (this->getJobEndTm() - this->getJobArrivalTm());
}


void Job::filePrintJob(ofstream &JobstatOut) {

    JobstatOut << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    JobstatOut << "Job ID: " << getJobID() << endl;
    JobstatOut << "Ran on: Virtual Machine " << getOnVM() << "  -  CPU " << getOnCPU() << endl;
    JobstatOut << "Timestamps (microseconds since Epoch):" << endl;
    JobstatOut << " Arrived in Queue @: " << chrono::duration_cast<chrono::microseconds>
            (this->getJobArrivalTm().time_since_epoch()).count() <<  endl;
    JobstatOut << "   Started on CPU @: " << chrono::duration_cast<chrono::microseconds>
            (this->getJobStartTm().time_since_epoch()).count() <<  endl;
    JobstatOut << "  Finished on CPU @: " << chrono::duration_cast<chrono::microseconds>
            (this->getJobEndTm().time_since_epoch()).count() << endl <<endl;
    JobstatOut << "Requested job length: " << chrono::duration_cast<chrono::microseconds>
            (this->getJobAssignedLeng()).count()<< " us" << endl;
    JobstatOut << "  Actual time on CPU: " << chrono::duration_cast<chrono::microseconds>
            ((this->getJobEndTm()) - (this->getJobStartTm())).count()<< " us" << endl;
    JobstatOut << endl;

}

