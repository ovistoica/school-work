#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

struct Node {
  vector<int> neighbors;
};

class Graph {
  private:
    int size;
    vector<Node> nodes;

    vector<int> topoTraverse() {
      vector<int> topoSortedNodes;
      vector<int> color(size, 0);

      if (dfs(0, color, topoSortedNodes)) {
        return vector<int>();
      }

      reverse(topoSortedNodes.begin(), topoSortedNodes.end());
      return topoSortedNodes;
    }

  	// Hint: Recursivitate
    // crt_node - nodul curent prin care trecem in parcurgere
    // color - vectorul de culori asociat fiecarui nod; este intializat cu 0
    // topoNodes - vectorul de populat cu nodurile sortate topologic
    bool dfs(int crt_node, vector<int>& color, vector<int>& topoNodes) {
      // TODO: implementati functia de traversare;
      // returnati true daca nu se poate realiza o sortare topologica
      // altfel returnati false
      color[crt_node] = 1;


      for(auto it = nodes[crt_node].neighbors.begin();
        it != nodes[crt_node].neighbors.end(); ++it){
          int v = *it;
          if(color[v] == 0){
            color[v] = 1;
            dfs(v, color, topoNodes);
          }
          else if (color[v] == 1){
            return true;
          }
        }
        color[crt_node] = 2;
        topoNodes.push_back(crt_node);

      return false;
    }

  public:
    Graph(int size) : size(size), nodes(size) { }
    ~Graph() { }

    void add_edge(int src, int dst) {
      assert(src < this->size && dst < this->size);
      nodes[src].neighbors.push_back(dst);
    }

    void printTopologicalSort() {
      vector<int> topoNodes = topoTraverse();

      assert(topoNodes.size() == 0 ||  topoNodes.size() == this->size);
      for (int i = 0; i < topoNodes.size(); ++i) {
        cout << topoNodes[i] << '\n';
      }

      if (topoNodes.size() == 0) {
        cout << "-1\n";
      }
    }
};

int main() {
  int nodes, edges;
  cin >> nodes >> edges;

  Graph g(nodes);

  for (int i = 0; i < edges; ++i) {
    int src, dst;
    cin >> src >> dst;
    g.add_edge(src, dst);
  }

  g.printTopologicalSort();

  return 0;
}
