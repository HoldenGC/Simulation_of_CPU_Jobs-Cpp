//
// Student Name: HoldenG
// Date: 03/01/2019
// Course:  Data Structures
// Assignment:  HW# 03 - Create a job queue simulation
//

#ifndef DATASTRUCT_HW03_VM_H
#define DATASTRUCT_HW03_VM_H

#include <vector>
#include "Job.h"
#include "CPU.h"
using namespace std;

class VM {

public:
    VM(int VMnum, int numCPU);      // Constructor to create a new machine
    vector<CPU> CPUs;               // Vector of CPU objects
};


VM::VM(int VMnum, int numCPU) {
    for (int i = 0; i < numCPU; i++){       // Each machine object needs a vector of CPU objects
        CPUs.push_back(*new CPU(VMnum,i));  // Create each CPU object with the ID of its machine
    }
}




#endif //DATASTRUCT_HW03_VM_H
