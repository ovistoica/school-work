#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <stack>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];
	vector<int> adjt[kNmax];
  vector<int> culoare;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		fin.close();
	}

	vector<vector<int>> get_result() {
		/*
		TODO: Gasiti componentele tare conexe ale grafului orientat cu
		n noduri, stocat in adj. Rezultatul se va returna sub forma
		unui vector, ale carui elemente sunt componentele tare conexe
		detectate. Nodurile si componentele tare conexe pot fi puse in orice
		ordine in vector.

		Atentie: graful transpus este stocat in adjt.
		*/
    culoare.resize(n+1, 0);
    stack<int> s;
		vector<vector<int>> sol;

    for(int i = 1; i <= n; ++i){
      if(culoare[i] == 0){
        dfs(i, s);
      }
    }
    for(int i = 1; i <= n; ++i){
      culoare[i] = 0;
    }

    int s_index = 0;
    while (!s.empty()){
      int node = s.top();
      s.pop();
      if(culoare[node] == 0){
        sol.push_back(vector<int>());
        dfsT(node, sol[s_index]);
        s_index++;
      }
    }
		return sol;
	}

  void dfs(int node, stack<int> &s){
    culoare[node] = 1;
    for(auto it = adj[node].begin(); it != adj[node].end(); ++it){
      if(culoare[*it] == 0){
        dfs(*it, s);
      }
    }
    s.push(node);
    culoare[node] = 2;
  }

  void dfsT(int node, vector<int> &sol){
    culoare[node] = 1;
    for(auto it = adjt[node].begin(); it != adjt[node].end(); ++it){
      if(culoare[*it] == 0){
        dfsT(*it, sol);
      }
    }
    sol.push_back(node);
    culoare[node] = 2;
  }

	void print_output(vector<vector<int>> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				fout << nod << ' ';
			}
			fout << '\n';
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
