//
// Created by - on 3/1/2019.
//

//
// Created by - on 2/21/2019.
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







#endif //DATASTRUCT_HW03_VM_H


