#include<iostream>
#include<string>
#include "Stack.h"
#include "Queue.h"
#include "Algorithms.h"
#include <deque>

int main() {

  std::string s;
  int n;
  std::cout << "Introdu paranteze" << std::endl;
  std::cin >> s;
  std::deque<char> deq;
  Stack<int, 30> *stack = new Stack<int, 30>();
  Queue<int, 30> *queue = new Queue<int, 30>();
  stack->

  //Paranthesis
  if(Algorithms().checkBalancedParentheses(s)) {
    std::cout << "Corect" << std::endl;
  } else {
    std::cout << "Incorrect" << std::endl;
  }

  //Reverse queue with stack
  std::cout << "Introdu numar elemente coada" << std::endl;
  std::cin >> n;
  for(int i = 0, e; i < n; i++){
    std::cin >> e;
    queue->enqueue(e);
  }
  std::cout << *queue << std::endl;
  while(!queue->isEmpty()) {
    stack->push(queue->dequeue());
  }
  while(!stack->isEmpty()) {
    queue->enqueue(stack->peek());
    stack->pop();
  }
  std::cout << *queue << std::endl;

  std::cout << "Introdu numar pt dequeue palindrom" << std::endl;
  std::cin >> s;
  for(char c : s) {
    deq.push_back(c);
  }

  //Palindrom Deq
  bool stillPali;
  char front, back;
  while(deq.size() > 1 && stillPali) {
    front = deq.front();
    back = deq.back();
    deq.pop_front();
    deq.pop_back();
    stillPali = (front == back);
  }
  if(stillPali) {
    std::cout << "Is palindrom" << std::endl;
  } else {
    std::cout << "Is not palindrom" << std::endl;
  }

  return 0;
}
