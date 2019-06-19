/* Copyright Stoica George Ovidiu 322CA */
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <iostream>
#include <cstring>
#include <queue>
#include <climits>

class Graph {
	int n;
	int m;
  int q;
  uint32_t **adj;
  std::vector<std::pair<int, int> > querries;

 public:
	void solve() {
		read_input();
    print_output(rev_edges());
	}

	// Allocating matrix after reading size
  void Graph_mat(){
    adj = new uint32_t*[n + 1];
		uint32_t my_inf = 100000;
    for(int i = 0; i < n + 1 ; i++){
      adj[i] = new uint32_t[n + 1];
    }
		// Putting cost 0 for the node to itself
		for(int i = 0; i < n + 1; i++){
			for(int j = 0; j < n + 1; j++){
				adj[i][j] = my_inf;
			}
			adj[i][i] = 0;
		}
  }

  ~Graph(){
    for(int i = 0; i < n + 1; i++){
      delete [] adj[i];
    }
    delete [] adj;
  }

 private:
	void read_input() {
		std::ifstream fin("revedges.in");
		fin >> n >> m >> q;
    Graph_mat();
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
      adj[x][y] = 0;
			// Verify if edge exists
			if (adj[y][x] != 0){
				adj[y][x] = 1;
			}
		}
    for (int i = 0, x, y; i < q; i++){
      fin >> x >> y;
      querries.push_back(std::make_pair(x,y));

    }

		fin.close();
	}

	void Floyd_Warshall(){
		for (int k = 1; k <= n; k++){
			for (int i = 1; i <= n; i++){
				for (int j = 1; j <= n; j++){
					if (adj[i][j] > adj[i][k] + adj[k][j])
						adj[i][j] = adj[i][k] + adj[k][j];
				}
			}
		}
	}

  std::vector<int> rev_edges(){
    std::vector<int> res;
		Floyd_Warshall();
    for (auto it = querries.begin(); it != querries.end(); ++it){
      int src = it->first;
      int dest = it->second;
			// Return the cost of matrix
			res.push_back(abs(adj[src][dest]));
    }
    return res;
  }

	void print_output(std::vector<int> out) {
		std::ofstream fout("revedges.out");
    for (auto it = out.begin(); it != out.end(); ++it){
      fout << *it << std::endl;
    }
		fout.close();
	}
};

int main() {
	Graph *g = new Graph();
	g->solve();
}
