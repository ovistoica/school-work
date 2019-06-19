#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
#include <climits>
using namespace std;

const int kNmax = 50005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}
	int n;
	int m;
	int source;
	vector<pair<int, int> > adj[kNmax];

 private:

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
		}
		fin.close();
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti distantele minime de la nodul source la celelalte noduri
		folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.
		*/
    auto d = Dijkstra();
		return d;
	}

  vector<int> Dijkstra(){
    vector<int> d(n+1, INT_MAX);
    vector<bool> selected(kNmax, false);
    d[source] = 0;
    for(auto e : adj[source]){
      d[e.first] = e.second;
    }
    auto cmp = [d] (int i, int j) { return d[i] < d[j]; };
    priority_queue<int, std::vector<int>, decltype(cmp)> Q(cmp);
    Q.push(source);
    while (!Q.empty()) {
      int u = Q.top();
      Q.pop();
      selected[u] = true;
      for(auto nod : adj[u]){
        if(!selected[nod.first] && (d[nod.first] > d[u] + nod.second)){
          d[nod.first] = d[u] + nod.second;
        }
      }
    }
    return d;
  }

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << " ";
		}
		fout << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
