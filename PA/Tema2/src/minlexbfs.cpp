/* Copyright Stoica George Ovidiu 322CA */
#include <vector>
#include <fstream>
#include <queue>
#include <cmath>
#include <algorithm>

const int kNmax = 100005;

class Graph{
private:
  int n;
  int m;
  std::vector<int> adj[kNmax];

public:
	void read_input() {
		std::ifstream fin("minlexbfs.in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
      adj[x].push_back(y);
      adj[y].push_back(x);
    }
    // Sorting neighbours for minlex BFS search
    for (int i = 1; i <= n; i++){
      sort(adj[i].begin(), adj[i].end());
    }
		fin.close();
	}

	void print_output(std::vector<int> result) {
		std::ofstream fout("minlexbfs.out");
		for (auto it = result.begin();it != result.end(); it++) {
			fout << *it << " ";
		}
		fout << "\n";
		fout.close();
	}

  std::vector<int> bfs(int node){
      std::vector<bool> visited(n + 1, false);
      std::queue<int> q;
      std::vector<int> sol;
      visited[node] = true;
      q.push(node);
      while (!q.empty()){
        int n = q.front();
        q.pop();
        for (auto it = adj[n].begin(); it != adj[n].end(); it++){
          if (!visited[*it]){
            visited[*it] = true;
            q.push(*it);
          }
        }
        sol.push_back(n);
      }
      return sol;
  }

	void solve() {
		read_input();
		print_output(bfs(1));
	}

};

int main() {
  Graph *g = new Graph();
  g->solve();
  delete g;
}
