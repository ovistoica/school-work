#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <climits>

using namespace std;

class Node {
public:
    unsigned int id;
    bool visited;
    unsigned int parent;

    Node(unsigned int id) {
        this->id = id;
        this->visited = false;
        this->parent = -1;
    }

    void visit() {
        visited = true;
    }

    bool is_visited() const {
        return visited;
    }

    unsigned int get_parent() const {
        return parent;
    }

    void set_parent(unsigned int p) {
        parent = p;
    }
};

class Graph {
public:
    vector<Node> nodes;
    std::vector<std::vector<unsigned int> > edges;
    Graph(unsigned int N) {
        edges.resize(N);
        for (unsigned int i = 0; i < N; i++)
            nodes.push_back(Node(i));
    }

    ~Graph() {

    }

    unsigned int get_node_count() const {
        return nodes.size();
    }

    void insert_edge(unsigned int node1, unsigned int node2) {
        if (node1 < edges.size())
            edges[node1].push_back(node2);
    }

};

int tarjan(Graph& g, int src, stack<int> &st, vector<int> idx, vector<int>low,
  int index, vector<bool> &in_stack){
  idx[src] = index;
  low[src] = index;
  index = index + 1;
  st.push(src);
  in_stack[src] = true;
  vector<unsigned int> neigh = g.edges[src];
  for(auto it = neigh.begin(); it != neigh.end(); ++it){
    int u = *it;
    if(idx[u] == -1){
      tarjan(g, u, st, idx, low, index, in_stack);
      low[src] = (low[src] < low[u]) ? low[src] : low[u];
    }
    else if(in_stack[u]){
      low[src] = (low[src] < idx[u]) ? low[src] : idx[u];
    }
  }
  if(low[src] == idx[src]){
    while(!st.empty()){
      int u = st.top();
      st.pop();
      if(u == src)break;
    }
    return 1;
  }
  return 0;
}

int comp_con(Graph& g)
{
  stack<int> st;
  vector<int>idx(g.get_node_count(), -1);
  vector<int>low(g.get_node_count(), -1);
  vector<bool>in_stack(g.get_node_count(), -1);
  int comp = 0;
  for(int i = 0; i < g.get_node_count(); i++){
    if(idx[i] == -1){
      comp = tarjan(g, i, st, idx, low, 0, in_stack);
    }

  }

    return 0;
}


int main(void) {
    unsigned int nr_nodes, nr_edges;
    cin >> nr_nodes >> nr_edges;

    Graph graph(nr_nodes);
    for (unsigned int i = 0; i < nr_edges; i++) {
        unsigned int id1, id2;

        cin >> id1 >> id2;
        graph.insert_edge(id1, id2);
        graph.insert_edge(id2, id1);
    }

    cout << comp_con(graph) <<  endl;

    return 0;
}
