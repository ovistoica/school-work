#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <climits>
using namespace std;

// DO NOT MODIFY
struct Node {
	vector<int> neighbors;
	string value;
} nd;

// DO NOT MODIFY
class Graph {
private:
	int size;
	vector<Node> nodes;

public:
	Graph(int s): size(s), nodes(s, nd) {}
	~Graph() {}

	int get_size() { return size; }

	void add_edge(int node1, int node2) { nodes[node1].neighbors.push_back(node2); }
	vector<int> get_neighbors(int node) { return nodes[node].neighbors; }

	string get_value(int id) { return nodes[id].value; }
	void set_value(int id, string val) { nodes[id].value = val; }
};

// DO NOT MODIFY
// Function to read graph data
Graph get_graph() {
	int n;
	cin >> n;
	Graph g (n);

	string line;
	getline(cin, line);
	for (int i = 0; i < n; i++) {
		getline(cin, line);

		istringstream iss(line);
	    for(int aux; iss >> aux; )
			g.add_edge(i, aux);
	}

	return g;
}

// DO NOT MODIFY
// Function to show the value of each node
void print_val(Graph g, int source) {
	for (int i = 0; i < g.get_size(); i++) {
		if (i != source) cout << g.get_value(i) << "\n";
	}
}


// Function to set the value of each node based on its distance from source
void set_value(Graph& g, int source, string value) {
 	// Write you code HERE!! (you can make any additional helper functions)
  for(int i = 0; i < g.get_size(); i++){
    if(i == source)continue;
    int distance = 0;
    queue<int> q;
    vector<bool> visited(g.get_size(), false);
    q.push(source);
    visited[source] = true;
    while(!q.empty()){
      ++distance;
      int u = q.front();
      q.pop();
      vector<int> neigh = g.get_neighbors(u);
      for(auto it = neigh.begin(); it != neigh.end(); ++it){
        int v = *it;
        if(v == i)
        if()
      }
    }
  }
}

// DO NOT MODIFY
int main(int argc, char* argv[]) {
	Graph g = get_graph();
	int source;
	cin >> source;
	string value;
	cin >> value;

	set_value(g, source, value);
	print_val(g, source);

 	return 0;
}
