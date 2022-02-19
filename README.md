# Simulation_of_CPU_Jobs-Cpp
C++ Program using arrays of objects holding arrays of objects to simulate jobs of randomly assigned lenghs being queued and then assigned to variable number of virtual machines with variable number of CPUs

## Simulation of CPU Jobs

This program simulates jobs which are of random assigned lengths
and have random delays between their arrival. All time values are
actual time values using <chrono> at sub-millisecond units.
 
The Simulation object creates a vector of Virtual Machine (VM) objects, each
one containing a vector of CPU objects.
 
The simulation also creates a Run Queue object for jobs that need to be
processed, and a Completed Queue object for jobs that are done. Both are
custom Template Linked Lists that hold Job objects.
 
### For each CPU of each VM, the following logic is performed:
 
- Test if a new job has "arrived" based on time comparison against
delay. If it has:
Create the job object, stamp time, place it into the Run Queue, and
increase Run Queue length. Write information about the queue event to
Queue Event CSV file (including the size of the queue) for import
into Excel to visualize time and queue size with scatterplot diagram.
Also test to see if the new job is the smallest or biggest so far.
 
- Test if the current CPU has a job and is done processing it (elapsed
time on cpu is longer than assigned length). If so, stamp time and move
job to Completed Queue. Also, if the final job was just moved to
completed queue, set simulation Done flag to true.
 
- Test if the current processor is ready and there is a job available
in the Run Queue. If so, stamp time, move job from Run Queue to the CPU,
and decrease Run Queue length. Write information about the queue event to
CSV file (including the new size of the queue).
 
- If the simulation is not done, move to next Machine/CPU

**Program Files:** 
- main.cpp // Main routine
- Sim.cpp // Simulation Object
- Sim.h
- MyList.h // Templated Linked List
- MyQueue.h // Extends MyList
- VM.cpp // Virtual Machine Obj
- VM.h
- CPU.cpp // CPU Obj
- CPU.h
- Job.cpp // Job Object
- Job.h

**Program Generated Output Files:**
- QueueSequence.csv // The order jobs enter and exit Run queue
- Done_Queue.txt // Entire listing of Job objs in done order

**Additional Files for Analysis and Visualization:**
- doneQueue300.xlsx // Excel graph of 300 job sequence
- doneQueue4000.xlsx // Excel graph of 4000 job sequence
