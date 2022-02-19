//
// Student Name: HoldenG
// Date: 03/01/2019
// Course:  Data Structures
// Assignment:  HW# 03 - Create a job queue simulation
//
#ifndef DATASTRUCT_HW03_MYQUEUE_H
#define DATASTRUCT_HW03_MYQUEUE_H

#include "MyList.h"
template <typename T>               // Template class which extends MyList
class MyQueue: public MyList<T> {

public:
    void enqueue(T& obj);           // Enqueue function
    T& dequeue();                   // Dequeue function
};

template <typename T>
void MyQueue<T>::enqueue(T& obj) {  // Sends Object to MyList->setRear function
    this->setRear(obj);
}

template<typename T>
T& MyQueue<T>::dequeue() {          // Retrieves object at front of MyList
    T& temp = this->getFront();
    this->killFront();              // Destroys front node
    return temp;
}


#endif //DATASTRUCT_HW03_MYQUEUE_H
