#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <tuple>
#include <climits>
#include <queue>
using namespace std;

const int kNmax = 2e5 + 10;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<pair<int, int> > adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
			adj[y].push_back(make_pair(x, w));
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Calculati costul minim al unui arbore de acoperire
		folosind algoritmul lui Prim.
		*/
    vector<int> parent(n + 1, -1);
    vector<int> dist(n + 1, INT32_MAX);
    vector<pair<int, int> > muchiiAMA;
    vector<bool> first(n + 1, false);
    int root = 1;
    int total_cost = 0;
    dist[root] = 0;
    parent[root] = -1;
    auto cmp = [dist] (int i, int j) { return dist[i] < dist[j]; };
    priority_queue<int, vector<int>, decltype(cmp)> heap(cmp);
    for(auto it = adj[root].begin(); it != adj[root].end(); ++it){
      dist[it->first] = it->second;
      parent[it->first] = root;
      heap.push(it->first);
    }
    while(!heap.empty()){
      int u = heap.top();
      heap.pop();
      if(!first[u] ){
        muchiiAMA.push_back(make_pair(u, parent[u]));
        first[u] = true;
        total_cost += dist[u];
      }
      for(auto it = adj[u].begin(); it != adj[u].end(); ++it){
        if(it->first == root){
          continue;
        }
        if(it->second < dist[it->first]){
          dist[it->first] = it->second;
          parent[it->first] = u;
          heap.push(it->first);
        }
      }
    }


		return total_cost;
	}


	void print_output(int result) {
		ofstream fout("out");
		fout << result << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
