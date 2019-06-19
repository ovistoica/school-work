#include <iostream>
#include <vector>

using namespace std;


class Node {
public:
    Node *next;
    string subject;
    int priority;

    Node(string subject, int priority) {
        this->subject = subject;
        this->priority = priority;
        this->next = nullptr;
    }
};

class PriorityQueue
{
private:
    int num_elements;
    Node *head;

public:
    PriorityQueue() {
        this->num_elements = 0;
        head = nullptr;
    }

    ~PriorityQueue() {
    }

    void push(string subject, int priority) {
        Node *paux = new Node(subject, priority);
        ++num_elements;
        if(head == nullptr){
          head = paux;
        } else if(head->priority > paux->priority){
          paux->next = head;
          head = paux;
        } else {
          Node *temp = head;
          Node *prev;
          while(temp->next != nullptr && temp->priority <= paux->priority){
            prev = temp;
            temp = temp->next;
          }
          if(temp->priority <= paux->priority){
            paux->next = temp->next;
            temp->next = paux;
          } else if(temp->priority > paux->priority)  {
            prev->next = paux;
            paux->next = temp;
          }
        }
    }

    Node *extractMin() {
        return nullptr;
    }

    bool isEmpty() {
        return num_elements == 0 ? true : false;
    }

    friend std::ostream& operator<<(std::ostream& os, PriorityQueue& queue);
};

std::ostream& operator<<(std::ostream& os, PriorityQueue& queue) {
    std::vector<Node *> aux;
    while (queue.head != nullptr) {
        aux.push_back(queue.head);
        queue.head = queue.head->next;
    }
    queue.num_elements = 0;
    for (unsigned int i = 0; i < aux.size(); i++) {
        os << aux[i]->subject << "\n";
    }

    return os;
}

int main() {
    int N;
    cin >> N;

    PriorityQueue pq;

    while (N > 0) {
        string s;
        int priority;
        cin >> s;
        cin >> priority;

        pq.push(s, priority);
        N--;
    }

    cout << pq;
    return 0;
}
