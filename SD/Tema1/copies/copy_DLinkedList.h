#include<iostream>
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__


/*Node class for the LinkedList */
template <typename T>
struct Node {
    T info;
    Node<T> *next, *prev;
};

/* DoublyLinkedList used for Deque */
template <typename T>
class DLinkedList {
    Node<T> *first;
    Node<T> *last;
    int contor;
public:
    DLinkedList():contor(0) {
        first = nullptr;
        last = nullptr;
    }

    ~DLinkedList() {
        if (!isEmpty()) {
            Node<T> *temp = first;
            while (temp != nullptr) {
                Node<T> *next = temp->next;
                delete temp;
                temp = next;
            }
        }
    }

    void printList() {
        Node<T> *temp = first;
        while (temp != nullptr) {
            std::cout << temp->info << "; ";
            temp = temp->next;
        }
    }

    bool isEmpty() {
      return (contor == 0);
    }

    void push_front(T info) {
        Node<T> *aux = new Node<T>;
        aux->info = info;
        aux->prev = nullptr;
        aux->next = first;
        if (isEmpty()) {
            last = first = aux;
        } else {
            first->prev = aux;
            first = aux;
        }
        ++contor;
    }

    void push_back(T info) {
        Node<T> *aux = new Node<T>;
        aux->info = info;
        aux->next = nullptr;
        aux->prev = last;
        if (isEmpty()) {
            last = first = aux;
        } else {
            last->next = aux;
            last = aux;
        }
        ++contor;
    }
    int size() {
      return contor;
    }

    T getFront() {
      return first->info;
    }

    T getBack() {
      return last->info;
    }

    void pop_back() {
        if (isEmpty()) {
            return;
        }
        Node<T> *temp = last;
        last = last->prev;
        if(last == nullptr) {
            first = nullptr;
        } else {
            last->next = nullptr;
        }
        delete temp;
        --contor;
    }

    void pop_front() {
        if (isEmpty()) {
            return;
        }
        Node<T> *temp = first;
        first = first->next;
        if (first == nullptr) {
            last = nullptr;
        } else {
            first->prev = nullptr;
        }
        delete temp;
        --contor;
    }

};
#endif
