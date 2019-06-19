#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <set>

const int MAX = 10000;
class Graph{
private:
	std::vector<unsigned int> adj[MAX];
	std::vector<unsigned int> adjt[MAX];
    unsigned int size;
public:
    // Constructor
    Graph(unsigned int size) {
        this->size = size;
    }

    // Destructor
    ~Graph() {}

    /**
     * Adds an edge between two existing nodes.
     * @param src Source node of the edge to be added.
     * @param dst Destination node of the edge to be added.
     */
    void addEdge(unsigned int src, unsigned int dst) {
      adj[src].push_back(dst);
      adjt[dst].push_back(src);
    }
    /**
    * Returns an array with nodes with maximum indegree
    * @return An array with nodes with maximum indegree
    */
    std::pair<uint32_t, uint32_t> maxInDegrees(){
      std::vector<unsigned int> degrees;
      unsigned int max = 0;
			unsigned int node = 0;
      for (unsigned int i = 1; i <= size; i++){
				uint32_t deg = nodeDegree(i);
				if(max < deg){
					max = deg;
					node = i;
				}
      }
			return std::make_pair(node,max);
    }

	std::vector<std::vector<unsigned int>> connex_comp() {
		/*
		Gasiti componentele tare conexe ale grafului orientat cu
		n noduri, stocat in adj. Rezultatul se va returna sub forma
		unui vector, ale carui elemente sunt componentele tare conexe
		detectate. Nodurile si componentele tare conexe pot fi puse in orice
		ordine in vector.

		Atentie: graful transpus este stocat in adjt.
		*/
    std::vector<int>culoare(size+1, 0);
    std::stack<int> s;
		std::vector<std::vector<unsigned int>> sol;

    for(uint32_t i = 1; i <= size; ++i){
      if(culoare[i] == 0){
        dfs(i, s, culoare);
      }
    }
    std::fill(culoare.begin(), culoare.end(), 0);

    uint32_t s_index = 0;
    while (!s.empty()){
      int node = s.top();
      s.pop();
      if(culoare[node] == 0){
        sol.push_back(std::vector<unsigned int>());
        dfsT(node, sol[s_index], culoare);
        s_index++;
      }
    }
		return sol;
	}

  void dfs(unsigned int node, std::stack<int> &s, std::vector<int> &culoare){
    culoare[node] = 1;
    for(auto it = adj[node].begin();
      it != adj[node].end(); ++it){
        if(culoare[*it] == 0){
          dfs(*it, s, culoare);
        }
    }
    s.push(node);
    culoare[node] = 2;
  }

  void dfsT(unsigned int node, std::vector<unsigned int> &sol, std::vector<int> &culoare){
    culoare[node] = 1;
    for(auto it = adjt[node].begin();
    it != adjt[node].end(); ++it){
      if(culoare[*it] == 0){
        dfsT(*it, sol, culoare);
      }
    }
    sol.push_back(node);
    culoare[node] = 2;
  }

    void bfs(unsigned int node, std::vector<bool> &visited){
      visited[node] = true;
      std::queue<unsigned int> q;
      q.push(node);
      while (!q.empty()){
        uint32_t n = q.front();
        q.pop();
        std::vector<unsigned int> neighbors = getNeighbors(n);
        for(uint32_t i = 0; i <= neighbors.size(); i++){
          if(!visited[i]){
              q.push(i);
              visited[i] = true;
          }
        }
      }
    }

    /**
    * Returns the indegree of a node
    * @return the indegree of a node
    */
    uint32_t nodeDegree(unsigned int node){
			return adjt[node].size();
    }


    /**
     * Gets the vector of neighbors associated with the given node.
     * @param node Node whose neighbors will get returned.
     * @return A vector containing the neighbors of the given node.
     */
    std::vector<unsigned int> getNeighbors(unsigned int node) {
        return adj[node];
    }

    /**
     * Gets the vector of neighbors associated with the given node.
     * @param node Node whose neighbors will get returned.
     * @return A vector containing the neighbors of the given node.
     */
    std::vector<unsigned int> getNeighborsT(unsigned int node) {
        return adjt[node];
    }

    /**
     * Gets the graph size.
     * @return Number of nodes in the graph.
     */
    unsigned int getSize() {
        return size;
    }
};

#endif // GRAPH_H__
