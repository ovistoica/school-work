#include <iostream>
#include <cstdio>
#include <vector>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> generateTest(int distinct, int repeatFactor) {
    vector<int> result;
    while (repeatFactor-- != 0) {
        for (int i = 0; i < distinct; ++i) {
            result.push_back(i);
        }
    }
    return result;
}

int countDistinct(const vector<int>& numbers) {
    // Create empty HashSet
    unordered_set<int> set;
    
    //TODO Process numbers from input. HINT: a HashSet contains only distinct elements
    for (int number : numbers) {
    }
    
    //TODO Return the number of distinct elements HINT: a HashSet contains only distinct elements
    return 0;
}

int main() {
    int repeatFactor = 3;
    int testsSizes[] = {10, 100, 1000, 10000};
    
    int numFailed = 0, numPassed = 0;
    
    for (int testSize : testsSizes) {
        vector<int> numbers = generateTest(testSize, repeatFactor);
        
        int reference = testSize;
        int candidate = countDistinct(numbers);
        
        if (reference != candidate) {
            printf("Expected %d distinct elements but got %d distinct elements\n",
                   reference, candidate);
            numFailed++;
        } else {
            numPassed++;
        }
    }
    
    printf("Passed: %d, Failed: %d\n", numPassed, numFailed);
    return 0;
}