/* Copyright Stoica George Ovidiu 322CA */
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <iostream>
#include <cstring>
#include <stack>
#include <unordered_map>
#include <list>

const int kNmax = 100005;

class Graph {
	int n;
	int m;
  int g_depth = 1;
	std::list<int> adj[kNmax];
	std::vector<int> depth;
	std::vector<int> low;
	std::stack<int> st;
	std::vector<bool> isInStack;
	std::vector<int> parent;
	unsigned int pairs = 0;

 public:
	void solve() {
		read_input();
		print_output();
	}

 private:

	void read_input() {
		std::ifstream fin("disjcnt.in");
		fin >> n >> m;
		depth.resize(n + 1, -1);
		low.resize(n + 1, -1);
		isInStack.resize(n + 1,false);
		parent.resize(n + 1, -1);
		for (int i = 0; i < kNmax; i++){
		}
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		for (int i = 1; i <= n; i++){
			adj[i].sort();
		}
		fin.close();
	}

  void getPairNumber(){
		g_depth = 1;
		// Delete critical edges
		for (int i = 1; i <= n; i++){
			if (depth[i] < 0){
				dfsB(i);
			}
		}

		g_depth = 1;
		std::fill(low.begin(), low.end(), -1);
		std::fill(depth.begin(), depth.end(), -1);
		for (int i = 1; i <= n; i++){
			if (depth[i] < 0){
				pairs += Tarjan(i);
			}
		}
	}

	int Tarjan(int i){
		depth[i] = low[i] = g_depth++;
		st.push(i);
		isInStack[i] = true;
		// Occurences for neighbours for checking double edge between nodes
		std::unordered_map<int, int> occ;


		for (auto it = adj[i].begin(); it != adj[i].end(); ++it){
			int v = *it;
			// Node not visited
			occ[v]++;
			if (depth[v] < 0){
				Tarjan(v);
				low[i] = (low[i] < low[v]) ? low[i] : low[v];
				// if there are two edges between the nodes
			} else if (isInStack[v]){
				low[i] = (low[i] < depth[v]) ? low[i] : depth[v];
			} else if (occ[v] > 1){
				low[i] = (low[i] < low[v]) ? low[i] : low[v];
			}
		}
		unsigned int cur_pairs = 0;;
		if(low[i] == depth[i]){
			int u;
			do {
				u = st.top();
				st.pop();
				isInStack[u] = false;
				cur_pairs++;
			}while (u != i);
		}

		// Check if it is not isolated node
		if (cur_pairs > 1){
			return (cur_pairs * (cur_pairs - 1)) / 2;
		}
		return 0;
	}

	// Function to remove critical edges
	void dfsB(int i){
		depth[i] = low[i] = g_depth++;
		std::unordered_map<int, int> occ;
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it){
			int v = *it;
			if (v == 0)continue;
			occ[v]++;
			// Check for double edge
			if (occ[v] > 1){
				low[i] = (low[i] < low[v]) ? low[i] : low[v];
			}else if (v != parent[i]){
				if (depth[v] < 0){
					parent[v] = i;
					dfsB(v);
					low[i] = (low[i] < low[v]) ? low[i] : low[v];
					// Eliminate critical edges
					if (low[v] > depth[i]){
						it = adj[i].erase(it);
						auto it2 = std::find(adj[v].begin(),adj[v].end(), i);
						if (it2 != adj[v].end())
							adj[v].erase(it2);
					}
				} else {
					low[i] = (low[i] < depth[v]) ? low[i] : depth[v];
				}
			}
		}
	}


	void print_output() {
		std::ofstream fout("disjcnt.out");
		getPairNumber();
		fout << pairs;
		fout << "\n";
		fout.close();
	}
};

int main() {
	Graph *g = new Graph();
	g->solve();
}
