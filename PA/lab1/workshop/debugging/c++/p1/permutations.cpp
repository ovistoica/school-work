#include <iostream>
#include <fstream>
#include <vector>

static int elementsNumber;
static int solutionsCounter;

//TODO There are 2 bugs in this function. Find them :)
void generatePermutations(std::vector<bool> &usedElements,
                          std::vector<int> &solution, int level)
{
    if (level == elementsNumber) {
        for (int value : solution) {
            std::cout << value << ' ';
        }
        std::cout << "\n";
        solutionsCounter++;
        return;
    }

    for (unsigned int i = 0; i < usedElements.size(); ++i) {
        if (!usedElements[i]) {
            usedElements[i] = true;
            solution[level] = i + 1;
            generatePermutations(usedElements, solution, ++level);
        }
    }
}

int main()
{
    std::ifstream fin("permutations.in");
    int testsNumber;
    fin >> testsNumber;
    for (int i = 0; i < testsNumber; ++i) {
        fin >> elementsNumber;
        std::cout << "Numbers interval: 1 - " << elementsNumber << "\n";
        std::cout << "Solutions:\n";

        solutionsCounter = 0;
        // true if i+1 was selected in the current partial solution, false otherwise
        std::vector<bool> usedElements(elementsNumber, false);
        // stores the solution
        std::vector<int> solution(elementsNumber, 0);

        generatePermutations(usedElements, solution, 0);
        std::cout << "Number of solutions: " << solutionsCounter << "\n\n";
    }
    return 0;
}
