#include <iostream>
#include <cstdio>
#include <vector>
#include <vector>
#include <unordered_set>
#include <random>
#include <set>

using namespace std;

enum OperationType {
    UPDATE,
    QUERY
};

struct Operation {
    OperationType type;
    int operand;
    
    Operation(OperationType type, int operand) {
        this->type = type;
        this->operand = operand;
    }
};

struct random {
    static int nextInt(int bound) {
        return rand() % (bound + 1);
    }
};

vector<int> randomvector(int size) {
    vector<int> result ;
    for (int i = 0; i < size; ++i) {
        result.push_back(random::nextInt(50));
    }
    return result;
}

vector<Operation> generateTest(const vector<int>& answers) {
    vector<Operation> result ;
    for (int answer : answers) {
        result.push_back(Operation(UPDATE, answer));
        while (random::nextInt(50) <= 10) {
            int number = random::nextInt(50);
            result.push_back(Operation(UPDATE, number));
        }
        result.push_back(Operation(QUERY, answer - 1));
    }
    return result;
}

vector<int> solve(vector<Operation> operations) {
    vector<int> result ;
    //TODO Create empty TreeSet
    
    for (const Operation& op : operations) {
        if (op.type == UPDATE) {
            //TODO update set of elements with op.operand
        }
        if (op.type == QUERY) {
            //TODO find first element greater than op.operand and add it to result.
            //TODO it is guaranteed that such an element exists
            //TODO HINT: TreeSet has a method which does exactly this
        }
    }
    return result;
}

int main() {
    srand(time(0));
    int tests[] = {10, 20, 30, 40};
    
    int failed = 0, passed = 0;
    for (int test : tests) {
        vector<int> reference = randomvector(test);
        vector<Operation> operations = generateTest(reference);
        vector<int> candidate = solve(operations);
        
        if (reference != candidate) {
            failed++;
            if (reference.size() != candidate.size()) {
                printf("Expected a vector of size %d, got a vector of size %d\n",
                       reference.size(), candidate.size());
                continue;
            }
            for (int i = 0; i < reference.size(); ++i) {
                if (reference.at(i) != candidate.at(i)) {
                    printf("Expected response %d at %d query, but got %d\n",
                           reference.at(i), i, candidate.at(i));
                }
            }
        } else {
            passed++;
        }
    }
    
    printf("Passed: %d, Failed: %d\n", passed, failed);
    return 0;
}