/* Copyright 2018 <Stoica George-Ovidiu>
  Copy this and a baby duck will cry */
#include<iostream>
#include<string>
#include<cstring>
#ifndef STACK_H_
#define STACK_H_

template<class T = int, int SIZE = 10>
class Stack {
    /* The resizeable array */
    T *resizeArray;
    int topLevel;
    int resize;

 public:
    /* Constructor */
    Stack(): topLevel(-1), resize(SIZE) {
        resizeArray = new T[SIZE];
    }

    /* Destructor */
    ~Stack() {
        if (resizeArray != NULL) {
            delete [] resizeArray;
        }
    }
    /**
     * Adds an element on top of the stack.
     * @param element Element to be added to the stack.
     */
    void push(T element) {
        if (size() >= resize) {
            T *temp;
            temp = new T[resize * 2];
            memcpy(temp, resizeArray, size() * sizeof(T));
            delete [] resizeArray;
            resizeArray = temp;
            resize *= 2;
        }
        resizeArray[++topLevel] = element;
    }

    /**
    * Prints the elements from the Stack
    * Used for debug purposes
    */
    void printStack() {
        for (int i = 0; i <= topLevel; i++) {
            std::cout << resizeArray[i] << " ";
        }
        std::cout << std::endl;
    }
    /**
    * Removes the top element of the stack
    */
    void pop() {
        if (topLevel < 0) {
            return;
        }
        topLevel--;
    }

    /**
    * Returns the capacity of the stack
    * @return The capacity of the stack
    */
    int getCapacity() {
        return resize;
    }

    /**
    * Checks if the stack contains any elements
    * @return True if the stack contains no elements, False otherwise
    */
    bool isEmpty() {
        return (topLevel < 0);
    }

    /**
    * Returns the top element of the Stack
    * @return top element from the Stack
    */
    T peek() {
        return resizeArray[topLevel];
    }

    /**
    * Returns the number of elements currently stored in the stack
    * @return The number of elements stored in the stack
    */
    int size() {
        return topLevel + 1;
    }
};
#endif  // STACK_H_
