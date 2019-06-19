#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

struct Value {
    int number, arrayIndex;

    Value(int number, int arrayIndex): number(number), arrayIndex(arrayIndex) {}
};


bool operator<(const Value &a, const Value &b)
{
    return a.number > b.number;
}

std::vector<int> doNMerge(const std::vector<std::vector<int> > &arrays)
{
    std::vector<int> result;

    // TODO 1: Declare priority_queue to hold Value elements
    // TODO 2: Use a vector to hold the last index used from every array
    // TODO 3: Add the first value from each array to the priority_queue
    // TODO 4: While you can, remove the smallest value from the priority_queue and add
    //		   the next value from the same array to the PriorityQueue
    //		   Hint: Verify if you still have a next element in that array.

    return result;
}

int main()
{
    std::ifstream fin("nmerge.in");
    int arraysNumber, value;
    fin >> arraysNumber;
    std::vector<int> arraysSize;
    for (int i = 0; i < arraysNumber; i++) {
        fin >> value;
        arraysSize.push_back(value);
    }
    std::vector<std::vector<int> > arrays(arraysNumber, std::vector<int>());
    std::vector<int> reference;
    for (int i = 0; i < arraysNumber; i++) {
        for (int j = 0; j < arraysSize[i]; j++) {
            fin >> value;
            arrays[i].push_back(value);
            reference.push_back(value);
        }
    }
    std::sort (reference.begin(), reference.end());

    std::vector<int> candidate = doNMerge(arrays);

    bool identical = false;
    if (reference.size() == candidate.size()) {
        auto mismatch_reference = std::mismatch(reference.begin(), reference.end(), candidate.begin());
        if (reference.end() == mismatch_reference.first) {
            identical = true;
        }
    }

    if (identical) {
        std::cout << "Congrats. The arrays were merged correctly.\n";
    } else {
        std::cout << "Too bad. The arrays were not merged correctly.\n";
    }

    return 0;
}
