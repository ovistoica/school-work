// copyright Luca Istrate, Andrei Medar

#include "./decisionTree.h"  // NOLINT(build/include)
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::string;
using std::pair;
using std::vector;
using std::unordered_map;
using std::make_shared;

// structura unui nod din decision tree
// splitIndex = dimensiunea in functie de care se imparte
// split_value = valoarea in functie de care se imparte
// is_leaf si result sunt pentru cazul in care avem un nod frunza
Node::Node() {
    is_leaf = false;
    left = nullptr;
    right = nullptr;
}

void Node::make_decision_node(const int index, const int val) {
    split_index = index;
    split_value = val;
}

void Node::make_leaf(const vector<vector<int>> &samples,
                     const bool is_single_class) {
    // TODO(you)
    // Seteaza nodul ca fiind de tip frunza (modificati is_leaf si result)
    // is_single_class = true -> toate testele au aceeasi clasa (acela e result)
    // is_single_class = false -> se alege clasa care apare cel mai des
    is_leaf = true;

    if (is_single_class) {
        result = samples[0][0];
    } else {
        vector<int> digits(10, 0);
        int pmax = 0;

        for (int i = 0; i < samples.size(); i++) {
            digits[samples[i][0]]++;

            if (digits[pmax] < digits[samples[i][0]]) {
                pmax = samples[i][0];
            }
        }

        for (int i = 0; i < digits.size(); i++) {
            if (digits[pmax] == digits[i]) {
                pmax = i;
                break;
            }
        }

        result = pmax;
    }
}

pair<int, int> find_best_split(const vector<vector<int>> &samples,
                               const vector<int> &dimensions) {
    // TODO(you)
    // Intoarce cea mai buna dimensiune si valoare de split dintre testele
    // primite. Prin cel mai bun split (dimensiune si valoare)
    // ne referim la split-ul care maximizeaza IG
    // pair-ul intors este format din (split_index, split_value)

    int splitIndex = -1, splitValue = -1;
    int tests = samples.size();
    float max = -20000;

    for (int i = 0; i < dimensions.size(); i++) {
        int mg = 1;

        vector<int> uniq = compute_unique(samples, dimensions[i]);
        for (auto it = uniq.begin(); it != uniq.end(); ++it){
            mg *= *it;
        }

        mg = floor(pow(mg, 1 / uniq.size()));

        pair<vector<int>, vector<int>> indexSplit;
        indexSplit = get_split_as_indexes(samples, dimensions[i], mg);

        if (!indexSplit.first.empty() && !indexSplit.second.empty()) {
            float leftEntropy = get_entropy_by_indexes(samples,
                 indexSplit.first);
            float rightEntropy = get_entropy_by_indexes(samples,
                 indexSplit.second);
            float parentEntropy = get_entropy(samples);

            float el1 = leftEntropy * indexSplit.first.size();
            float el2 = rightEntropy * indexSplit.second.size();

            float informationGain = parentEntropy - (el1 + el2) / tests;

            if (informationGain > max) {
                max = informationGain;
                splitIndex = dimensions[i];
                splitValue = mg;
            }
        }
    }

    return pair<int, int>(splitIndex, splitValue);
}

void Node::train(const vector<vector<int>> &samples) {
    // TODO(you)
    // Antreneaza nodul curent si copii sai, daca e nevoie
    // 1) verifica daca toate testele primite au aceeasi clasa (raspuns)
    // Daca da, acest nod devine frunza, altfel continua algoritmul.
    // 2) Daca nu exista niciun split valid, acest nod devine frunza. Altfel,
    // ia cel mai bun split si continua recursiv

    if (same_class(samples)) {
        make_leaf(samples, true);
    } else {
        vector<int> dimensions = random_dimensions(samples[0].size());
        pair<int, int> bestSplit = find_best_split(samples, dimensions);

        if (bestSplit.first == -1) {
            make_leaf(samples, false);
        } else {
            make_decision_node(bestSplit.first, bestSplit.second);
            pair<vector<vector<int>>, vector<vector<int>>> getSplit;
            getSplit = split(samples, bestSplit.first, bestSplit.second);

            left = make_shared<Node>();
            left->train(getSplit.first);

            right = make_shared<Node>();
            right->train(getSplit.second);
        }
    }
}

int Node::predict(const vector<int> &image) const {
    // TODO(you)
    // Intoarce rezultatul prezis de catre decision tree
    if (is_leaf) {
        return result;
    } else {
        if (image[split_index - 1] <= split_value) {
            return left->predict(image);
        } else {
            return right->predict(image);
        }
    }
}

bool same_class(const vector<vector<int>> &samples) {
    // TODO(you)
    // Verifica daca testele primite ca argument au toate aceeasi
    // clasa(rezultat). Este folosit in train pentru a determina daca
    // mai are rost sa caute split-uri
    for (unsigned int i = 0; i < samples.size() - 1; i++) {
        if (samples[i][0] != samples[i + 1][0]) {
            return false;
        }
    }

    return true;
}

float get_entropy(const vector<vector<int>> &samples) {
    // Intoarce entropia testelor primite
    assert(!samples.empty());
    vector<int> indexes;

    int size = samples.size();
    for (int i = 0; i < size; i++) indexes.push_back(i);

    return get_entropy_by_indexes(samples, indexes);
}

float get_entropy_by_indexes(const vector<vector<int>> &samples,
                             const vector<int> &index) {
    // TODO(you)
    // Intoarce entropia subsetului din setul de teste total(samples)
    // Cu conditia ca subsetul sa contina testele ale caror indecsi se gasesc in
    // vectorul index (Se considera doar liniile din vectorul index)
    vector<float> pi(10, 0);
    float entropy = 0.0;
    float indexes = (float)index.size();
    float tests = (float)samples.size();

    for (int i = 0; i < indexes; i++) {
        pi[samples[i][0]]++;
    }

    for (int i = 0; i < pi.size(); i++) {
        if (pi[i]) {
            entropy = entropy - pi[i] / tests * log2(pi[i] / tests);
        }
    }

    return entropy;
}

vector<int> compute_unique(const vector<vector<int>> &samples, const int col) {
    // TODO(you)
    // Intoarce toate valorile (se elimina duplicatele)
    // care apar in setul de teste, pe coloana col
    vector<int> uniqueValues;

    for (int i = 0; i < samples.size(); i++) {
        if (std::find(uniqueValues.begin(), uniqueValues.end(),
             samples[i][col]) == uniqueValues.end()) {
             uniqueValues.push_back(samples[i][col]);
        }
    }

    return uniqueValues;
}

pair<vector<vector<int>>, vector<vector<int>>> split(
    const vector<vector<int>> &samples, const int split_index,
    const int split_value) {
    // Intoarce cele 2 subseturi de teste obtinute in urma separarii
    // In functie de split_index si split_value
    vector<vector<int>> left, right;

    auto p = get_split_as_indexes(samples, split_index, split_value);
    for (const auto &i : p.first) left.push_back(samples[i]);
    for (const auto &i : p.second) right.push_back(samples[i]);

    return pair<vector<vector<int>>, vector<vector<int>>>(left, right);
}

pair<vector<int>, vector<int>> get_split_as_indexes(
    const vector<vector<int>> &samples, const int split_index,
    const int split_value) {
    // TODO(you)
    // Intoarce indecsii sample-urilor din cele 2 subseturi obtinute in urma
    // separarii in functie de split_index si split_value
    vector<int> left, right;

    for (int i = 0; i < samples.size(); i++) {
        if (samples[i][split_index] <= split_value) {
            left.push_back(i);
        } else {
            right.push_back(i);
        }
    }

    return make_pair(left, right);
}

vector<int> random_dimensions(const int size) {
    // TODO(you)
    // Intoarce sqrt(size) dimensiuni diferite pe care sa caute splitul maxim
    // Precizare: Dimensiunile gasite sunt > 0 si < size
    vector<int> rez;

    int dimensions = floor(sqrt(size));
    int dimension;

    // unsigned int seed = time(0);
    // srand(seed);

    for (int i = 0; i < dimensions; i++) {
        do {
            // dimension = rand_r(&seed) % size;
            dimension = random() % size;
        } while ((std::find(rez.begin(), rez.end(), dimension) != rez.end())
            || !dimension);

        rez.push_back(dimension);
    }
    return rez;
}
