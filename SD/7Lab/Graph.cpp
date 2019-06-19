#include "Graph.h"

/*
	Constructor
*/
Graph::Graph(int n, bool oriented) {
	this->numNodes = n;
	this->oriented = oriented;
	for (int i = 0; i < numNodes; i++) {
		neigh.push_back(vector<int>());
	}
}

/*
	Adds an edge to the graph (both ways if unoriented)
*/
void Graph::addEdge(int i, int j) {
	neigh[i].push_back(j);
	if (!oriented) {
		neigh[j].push_back(i);
	}
}

/*
	Checks if two nodes are connected by an edge
*/
bool Graph::isEdge(int i, int j) {
	vector<int> v = neigh[i];
	return std::find(v.begin(), v.end(), j) != v.end();
}

void Graph::connectedComponents() {

	/* TODO 1 Initializations */
	numConnectedComp = -1;
	vector<bool> visited(numNodes,false);

	/*
		TODO 1 Call dfs for all unvisited nodes

		Use: components.push_back(vector<int>());
			to create new component
	*/
	for(int i = 0; i < numNodes; i++){
			if(!visited[i]){
				++numConnectedComp;
				components.push_back(vector<int>());
				dfs(i, visited);
			}
	}
	numConnectedComp++;

}

void Graph::dfs(int node, vector<bool>& visited) {
	/*
		TODO 1 Perform dfs
			To add node to component use:
			components[numConnectedComp].push_back(node);
	*/
	visited[node] = true;
	components[numConnectedComp].push_back(node);
	vector<int> node_neigh= neigh[node];
	for(auto it = node_neigh.begin(); it != node_neigh.end(); ++it){
			if(!visited[*it]){
				visited[*it] = true;
				dfs(*it, visited);
			}
	}
	for(int i = 0; i < numConnectedComp; i++){
		for(int j = 0; j < components[i].size(); j++){
			cout << components[i][j] << " ";
		}
		cout << endl;
	}
}

stack<int> Graph::minPath(int source, int dest) {
	vector<bool> visited;
	std::queue<int> q;
	vector<int> dist;
	vector<int> parent(numNodes);

	/* TODO 2 Initializations */

	/*
		TODO 2 Perform BFS from source, keeping track of distance and parent
	*/

	stack<int> path;
	// There is no path from source to destination
	if (parent[dest] == -1) return path;

	/*
		TODO 2 Start from destination, node becomes its parent and gets
		pushed onto the stack while source is not reached
	*/

	return path;
}

/*
	Comparator for finTime used in topologicalSort
*/
struct comp {
	vector<int> finTime;
	comp(vector<int>& finTime) {
		this->finTime = finTime;
	}
	bool operator()(int i, int j) const {
		return finTime[i] > finTime[j];
	}
};

vector<int> Graph::topSort() {
	vector<bool> visited;
	vector<int> topSortOrder;
	finTime.resize(numNodes);

	for (int i = 0; i < numNodes; i++) {
		/*
			TODO 3 Initialize visited
		*/
		topSortOrder.push_back(i);
	}

	/*
		TODO 3 Call dfsTopSort for each unvisited node
	*/

	comp c(finTime);

	// Nodes sorted in descending order by finTime
	sort(topSortOrder.begin(), topSortOrder.end(), c);
	return topSortOrder;
}
void Graph::dfsTopSort(int n, vector<bool>& visited) {
	/*
		TODO 3 Perform DFS keeping track of finTime
	*/
}

bool Graph::isBipartite(pair<vector<int>, vector<int> >& p) {
	vector<int> sides[2];
	vector<Tag> tag(numNodes);
	queue<int> q;

	/*
		4 Initialize all tags with UNDEFINED
	*/
	tag.resize(numNodes, UNDEFINED);

	tag[0] = PAR;
	q.push(0);

	/*
		 4 Perform BFS, marking the tags accordingly
	*/
	while(!q.empty()){
		int node = q.front();
		q.pop();
		vector<int> node_neigh = neigh[node];
		for(auto it = node_neigh.begin(); it != node_neigh.end(); ++it){
			if(tag[*it] == UNDEFINED){
				//tag[*it] = (tag[node] == PAR)? IMPAR : PAR;
				if(tag[node] == PAR){
					tag[*it] = IMPAR;
				} else {
					tag[*it] = PAR;
				}
				q.push(*it);
			} else if (tag[*it] == tag[node]){
				return false;
			}
		}

	}

	/*
		4 sides[0] will contain nodes with PAR tag and sides[1]
		the nodes with IMPAR tag

		To add node to one side: sides[x].push_back(node);
	*/
	for(int i = 0; i < numNodes; i++){
		if(tag[i] == PAR){
			sides[0].push_back(i);
		} else {
			sides[1].push_back(i);
		}
	}

	p = make_pair(sides[0], sides[1]);
	return true;
}
void Graph::hamiltonianCycles() {
	vector<bool> included(numNodes, false);
	vector<int> path(numNodes, -1);

	/*
		TODO BONUS Start constructing path from node 0
	*/
}

bool hasEdge(int x, int y){
	bool one = false, two = false;
	for(int i = 0; i < neigh[x].size(); i++){
		if(i == y){
			one = true;
			break;
		}
	}
	for(int i = 0; i < neigh[y].size(); i++){
		if(i == x){
			two = true;
			break;
		}
	}

	return one;
}

bool Graph::buildPath(vector<int>& path, vector<bool>& included, int length) {
	/*
		TODO BONUS Check if path represents a hamiltonian cycle and add it to the list:
				hamCycles.push_back(path);

			Otherwise try to include each node to the path.

			Path already has the right size, use [] operator not push_back!
	*/
	if(length == numNodes){
		int end = path.back();
		int start = path.front();
		if(hasEdge(start, end)){
			return true;
		}
	} else {
		for(int i = 0; i < numNodes; i++){
			int end = path.back();
			if(hasEdge(end, i)){
				buildPath(path, included,length + 1);
			}
		}
	}



	return false;
}
