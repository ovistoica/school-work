#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int kNmax = 1005;

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
  int C[kNmax][kNmax];
  int f[kNmax][kNmax];
  vector<int> parent;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		memset(C, 0, sizeof C);
		memset(f, 0, sizeof f);
    parent.resize(n + 1, -1);

		for (int i = 1, x, y, z; i <= m; i++) {
			fin >> x >> y >> z;
			adj[x].push_back(y);
			adj[y].push_back(x);
      C[x][y] += z;
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Calculati fluxul maxim pe graful orientat dat.
		Sursa este nodul 1.
		Destinatia este nodul n.

		In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
		arcelor, iar in C sunt stocate capacitatile arcelor.
		De exemplu, un arc (x, y) de capacitate z va fi tinut astfel:
		C[x][y] = z, adj[x] contine y, adj[y] contine x.
		*/
		int flow = 0;
    while(true){
      vector<pair<int, int> >path = BFS(1, n);
      if(path.empty()) break;
      int cf = INT32_MAX;
      for(auto it = path.begin(); it != path.end(); ++it){
        int u = it->first;
        int v = it->second;
        if(C[u][v] - f[u][v] < cf){
          cf = C[u][v] - f[u][v];
        }
      }
      flow += cf;
      for(auto it = path.begin(); it != path.end(); ++it){
        int u = it->first;
        int v = it->second;
        f[u][v] += cf;
        f[v][u] -= cf;
      }
    }
    return flow;
	}

  vector<pair<int,int> > BFS (int node, int dest){
    vector<int> wasHere;
    queue<int> Q;
    Q.push(node);
    bool notThereYet = true;
    while(!Q.empty() && notThereYet){
      int n = Q.front();
      wasHere.push_back(n);
      Q.pop();
      for(auto it = adj[n].begin(); it!= adj[n].end(); ++it){
          int ni = *it;
          if(C[n][ni] == f[n][ni]){
            continue;
          }
          if(find(wasHere.begin(), wasHere.end(), ni) != wasHere.end()){
            continue;
          }
          if(ni == dest){
            parent[dest] = n;
            notThereYet = false;
            break;
          }
          Q.push(ni);
          parent[ni] = n;
      }
    }

    if(notThereYet){
      return vector<pair<int, int> >();
    }
    int cur = dest;
    vector<pair<int, int> > path;
    while(cur != node){
      path.push_back(make_pair(parent[cur], cur));
      cur = parent[cur];
    }
    return path;
  }

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
