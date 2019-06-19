/**
 * LabSD 4
 * Algorithms.h
 * Purpose: Wrapper class for Lab4 algorithms.
 *
 * @author Gabriel Bercaru
 */

#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <string>
#include <vector>

#include "Queue.h"
#include "Stack.h"

class Algorithms {
public:
    /**
     * Checks if the input string represents a balanced parentheses sequence.
     *
     * @param str String representing the sequence of brackets to be checked.
     * @return True if the sequence of brackets is balanced, False otherwise.
     */
    static bool checkBalancedParentheses(std::string str) {
      Stack<char, 30> *s = new Stack<char, 30>();
      for(char c : str) {
        if(c == '[' || c == '{' || c == '(') {
          std::cout << "in: "<< c << " ";
          s->push(c);
        }
        if((c == ']' && s->peek() == '[')
        || (c == '}' && s->peek() == '{')
        || (c == ')' && s->peek() == '(')) {
          std::cout << "out: "<< c << " ";
          s->pop();
        }
      }
      return s->isEmpty();
	  asd a
    }

    /**
     * Apply radix sort on the given vector.
     * Does not return anything, the vector
     * given as parameter must contain the
     * sorted elements.
     *
     * @param v Vector of elements to be sorted.
     */
    static void radixSort(std::vector<int>& v) {
        // TODO: TASK 4
    }

    /**
     * Reverses the given queue.
     * Does not return anything, the queue
     * given as parameeter must contain
     * the elements, in reverse order.
     *
     * @param queue Queue to be reversed.
     */
    template <typename T>
    static void reverseQueue(Queue<T, 20>& queue) {
        // TODO: BONUS 1
    }
};

#endif // __ALGORITHMS_H__
