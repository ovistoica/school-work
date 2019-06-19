#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int kMod = 1e9 + 7;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result() {
		/*
		Calculati numarul de subsiruri ale lui v cu suma numerelor para si
		returnati restul impartirii numarului la 10^9 + 7.
		*/

		vector<int> par (n + 1);
		vector <int> impar(n + 1);
		if(v.at(1) % 2 == 0) {
			par[1] = 1;
			impar[1] = 0;
		} else {
			par.at(1) = 0;
			impar.at(1) = 1;
		}

		for(int i = 2; i <= n; i++) {
			if(v[i] % 2 == 0) {
				par[i] = 2 * par[i - 1] + 1;
				impar[i] = impar[i - 1] * 2;
			} else {
				par[i] = par[i - 1] + impar[i - 1];
				impar[i] = impar[i - 1] + par[i - 1] + 1;
			}
		}

		return par[n] % (long long)(pow(10, 9) + 7);
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
