//
//  MaxHeap.cpp
//  ScrabbleSolver
//
//  Created by Jeff Nainaparampil on 6/4/13.
//

#include "MaxHeap.h"

// To construct heap, simply have to set the heap count to 0
MaxHeap::MaxHeap()
{
    currentTail = 0;
}

// Inserts a value into MaxHeap by iterating through already
// constructed one.
MaxHeap::MaxHeap(const MaxHeap &copy)
{
    currentTail = copy.currentTail;
    for (int i = 0; i < currentTail; i++)
        nodes[i] = copy.nodes[i];
}

// Nothing needs be done, because we don't
// any pointers in our class, everything is
// stored in the runtime stack.
MaxHeap::~MaxHeap()
{
}

// Inserts item at the end of the array,
// then bubbles up, and finally increments tail.
void MaxHeap::insert(string item, int priority)
{
    // First add the element to the tail
    MaxHeapNode newNode;
    newNode.priority = priority;
    newNode.word = item;
    
    nodes[currentTail] = newNode;
    bubbleUp(currentTail);
    
    currentTail++;
}

// Recursively bubbles up the heap.
void MaxHeap::bubbleUp(int index)
{
    // Check if reached the top of the heap:
    if (index > 0) {
        // Check if parent is bigger, if so bubble up
        // else stop.
        int parentIndex = (index - 1) / 2;
    
        if (nodes[parentIndex].priority < nodes[index].priority)
        {
            MaxHeapNode tempNode = nodes[parentIndex];
            nodes[parentIndex] = nodes[index];
            nodes[index] = tempNode;
            bubbleUp(parentIndex);
        }
    }
}

// Checks if heap is empty by simply checking if currentTail
// is zero.
bool MaxHeap::isEmpty()
{
    return !currentTail;
}

// Returns the max without popping it.
string MaxHeap::peekMax()
{
    return nodes[0].word;
}

// Returns the max, and then removes it.
string MaxHeap::dequeueMax()
{
    // If the heap is empty, return an empty string
    if (isEmpty()) return "";
    
    // Decrement the current tail
    currentTail--;
    
    // Store the head, and then replace
    // the head with the tail word.  The tail word is now
    // where we're going to insert the newest element (if there is one).
    string word = nodes[0].word;
    nodes[0] = nodes[currentTail];
    
    bubbleDown(0);
    
    return word;
}

// Recursively performs the bubble down mechanism
void MaxHeap::bubbleDown(int index)
{
    int leftChild = 2*index + 1;
    int rightChild = 2*index + 2;
    
    // Recurse until the end of the heap is reached
    if (leftChild < currentTail)
    {
        MaxHeapNode tempNode = nodes[index];
        
        // Check which of the two child nodes is bigger
        // Also checks if rightChild is outside of the heap
        if (nodes[leftChild].priority > nodes[rightChild].priority || rightChild >= currentTail)
        {
            // Check if the parent is bigger
            if (nodes[leftChild].priority > nodes[index].priority)
            {
                nodes[index] = nodes[leftChild];
                nodes[leftChild] = tempNode;
                bubbleDown(leftChild);
            }
        }
        else
        {
            if (nodes[rightChild].priority > nodes[index].priority)
            {
                nodes[index] = nodes[rightChild];
                nodes[rightChild] = tempNode;
                bubbleDown(rightChild);
            }
        }
    }
}