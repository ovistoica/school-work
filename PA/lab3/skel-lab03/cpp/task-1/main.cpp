#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, S;
	vector<int> v;

  int get_coin_no(int *dp, int k) {
      int no_coins_i, min = INT_MAX;
      for(int i = 1; i < k; i++) {
          no_coins_i = dp[k - i];
          if(no_coins_i < 0) {
            continue;
          }
          if(min > no_coins_i + 1) {
            min = no_coins_i + 1;
          }
      }
      return min;
  }

	void read_input() {
		ifstream fin("in");
		fin >> n >> S;
		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Aflati numarul minim de monede ce poate fi folosit pentru a obtine
		suma S. Tipurile monedelor sunt stocate in vectorul v, de dimensiune n.
		*/

    int dp[S];
    dp[0] = 0;
    for(int i = 1; i < n; i++) {
        dp[i] = get_coin_no(dp, i);
    }
		return dp[S];
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
