//
//  MaxHeap.h
//  ScrabbleSolver
//
//  Created by Jeff Nainaparampil on 6/4/13.
//  Copyright (c) 2013 Jeff Nainaparampil. All rights reserved.
//

#ifndef __ScrabbleSolver__MaxHeap__
#define __ScrabbleSolver__MaxHeap__

#include <iostream>
using namespace std;

struct MaxHeapNode
{
    int priority;
    string word;
};

class MaxHeap
{
private:
    MaxHeapNode nodes[10000];
    int currentTail;
protected:
    void bubbleUp(int index);
    void bubbleDown(int index);
public:
    MaxHeap(); // Default constructor
    MaxHeap(const MaxHeap &copy); // Copy constructor
    ~MaxHeap(); // destructor for heap
    void insert(string item, int priority); // inserts a node into the heap
    bool isEmpty(); // checks if the number of 
    string peekMax(); // return just the head
    string dequeueMax(); // return and remove the head
};

#endif /* defined(__ScrabbleSolver__MaxHeap__) */
