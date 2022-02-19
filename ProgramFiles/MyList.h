//
// Student Name: HoldenG
// Date: 03/01/2019
// Course:  Data Structures
// Assignment:  HW# 03 - Create a job queue simulation
//
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class MyList {



private:
    struct myNode {                 // Wrapper structure
        T* aDataElem = nullptr;     // Address of data object
        myNode* aNext = nullptr;    // Address of next node
        myNode* aPrev = nullptr;    // Address of previous node
    };

    myNode* aStart;                 // Address of list start
    myNode* aEnd;                   // Address of list end
    myNode* aTemp;                  // Address of NEW NODE
    myNode* aMarker;                // Address of temporary marker

    int length;                     // Counter of elements in list
    myNode* aTraverse;              // Address of TRACKER


public:
    MyList();
    void firstNode(T &aDataObj);    // Creates element in empty list
    bool nextElem();                // Moves to next element
    bool isLast();                  // Check for next pointer of null
    bool isEmpty();                 // Check for start pointer of null

    int getLength();
    bool firstElem();
    T& currElem();
    T copyElem();
    T& getFront();
    T getRear();
    T elemAt(int index);
    void setFront(T& aDataObj);
    void setRear(T& aDataObj);
    void killFront();
    void killRear();
    void markCurrent() ;
    void restoreMark();

};

// Constructor for MyList object - initialize pointers to NULL and length to 0
template<class T>
MyList<T>::MyList() {
    this->aStart = nullptr;
    this->aTraverse = nullptr;
    this->aTemp = nullptr;
    this->aEnd = nullptr;
    this->length = 0;
}

// Return length of MyList Object
template<typename T>
int MyList<T>::getLength() {
    return (this->length);
}

// Test for no current node (empty list)
template<typename T>
bool MyList<T>::isEmpty() {
    return (!(aStart));
}

template<typename T>
bool MyList<T>::firstElem() {
    aTraverse = aStart;
    if (aStart) {
        return true;
    } else {
        return false;

    }
}

template<typename T>
T& MyList<T>::currElem() {
    return *aTraverse->aDataElem;
}

template<typename T>
T MyList<T>::copyElem() {
    return *aTraverse->aDataElem;
}

template<typename T>
bool MyList<T>::nextElem() {
    if (!isLast()) {
        aTraverse = aTraverse->aNext;
        return true;
    } else {
        return false;
    }
}


// Test for no next node (currently last node)
template<typename T>
bool MyList<T>::isLast() {
    return (!(aTraverse->aNext));
}


template<typename T>
void MyList<T>::firstNode(T& aDataObj) {
    aStart = new myNode;                        // Create new node and set starting address to it
    aEnd = aStart;                              // Set ending address to new node
    this->length = 1;                           // Increment length counter
    aStart->aDataElem = &aDataObj;              // Place new aDataElem into new starting node
    aStart->aNext = nullptr;                    // Set starting node's next address to NULL
}

template<typename T>
void MyList<T>::setFront(T& aDataObj) {
    if (this->isEmpty()) {
        firstNode(aDataObj);
    } else {
        aTemp = new myNode;
        (this->length)++;                       // Place passed aData into new starting node
        aTemp->aNext = aStart;
        aStart->aPrev = aTemp;
        aStart = aTemp;
        aStart->aDataElem = &aDataObj;
    }
}

template<typename T>
T& MyList<T>::getFront() {
    if (isEmpty())
        throw out_of_range("** No element to get");
    return *(aStart->aDataElem);
}

template<typename T>
void MyList<T>::killFront() {
    if (isEmpty())
        throw out_of_range("** No element to remove");
    if (length == 1) {
        delete aStart;
        aStart = nullptr;
        aEnd = nullptr;
        this->length = 0;
    } else {
        aTemp = aStart->aNext;
        delete aStart;
        aStart = aTemp;
        aStart->aPrev = nullptr;
        (this->length)--;
    }
}


template<typename T>
void MyList<T>::setRear(T& aDataObj) {
    if (this->isEmpty()) {
        firstNode(aDataObj);
    } else {
        aTemp = new myNode;
        (this->length)++;                       // Place new aDataElem into new starting node
        aEnd->aNext = aTemp;
        aTemp->aPrev = aEnd;
        aEnd = aTemp;
        aEnd->aDataElem = &aDataObj;
    }
}

template<typename T>
T MyList<T>::getRear() {
    if (isEmpty())
        throw out_of_range("** No element to get");
    return *(aEnd->aDataElem);
}

template<typename T>
void MyList<T>::killRear() {
    if (isEmpty())
        throw out_of_range("** No element to remove");
    if (length == 1) {
        delete aStart->aDataElem;
        delete aStart;
        aStart = nullptr;
        aEnd = nullptr;
        this->length = 0;
    } else {
        aTemp = aEnd->aPrev;
        delete aEnd->aDataElem;
        delete aEnd;
        aEnd = aTemp;
        aEnd->aNext = nullptr;
        (this->length)--;
    }
}

template<typename T>
T MyList<T>::elemAt(int index) {
    if (index <= this->length) {
        this->firstElem();
        for (int i = 0; i < index; i++) {
            this->nextElem();
            cout << i << "\n";
        }
        return this->copyElem();
    } else throw out_of_range(" Index out of range");
}

template<typename T>
void MyList<T>::markCurrent() {
    this->aMarker = this->aTraverse;
}

template<typename T>
void MyList<T>::restoreMark() {
    this->aTraverse = this->aMarker;
}





