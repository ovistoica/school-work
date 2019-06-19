#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Word {
private:
    string word;
    int max_freq = 0;
    unordered_map<char, int> freq;
    vector<char> max_freqs;

public:
    Word(string s) {
        this->word = s;
        this->max_freq = 0;
    }

    ~Word() {

    }

    void get_common_letters() {
      for(auto it = word.begin(); it != word.end(); ++it){
        freq[*it]++;
        if(freq[*it] > max_freq) max_freq = freq[*it];
      }
      string abc = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
      for(auto it = abc.begin(); it != abc.end(); ++it){
        if(freq[*it] == max_freq){
          max_freqs.push_back(*it);
        }
      }
    }

    void print() {
        cout << word << ": ";
        sort(max_freqs.begin(), max_freqs.end());
        for (unsigned int i = 0; i < max_freqs.size(); i++)
            cout << max_freqs[i] << " ";
        cout << ": " << max_freq << endl;
    }
};

int main() {
    int N;
    cin >> N;

    while (N > 0) {
        string s;
        cin >> s;

        Word word(s);
        word.get_common_letters();
        word.print();
        N--;
    }

    return 0;
}
