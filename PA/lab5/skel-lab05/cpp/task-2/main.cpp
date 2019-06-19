#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	vector<vector<int> > get_result() {
		vector<vector<int> > all;

		/*
		TODO: Construiti toate submultimile multimii {1, ..., N}.

		Pentru a adauga o noua submultime:
			vector<int> submultime;
			all.push_back(submultime);
		*/

		return all;
	}

  void back(int pivot, std::vector<int> &domain,
    std::vector<int> &solution, std::vector<vector<int>> &all) {
      for (; i < domain.size(); ++i) {
        solution[step] = i;
        back(step + 1, stop, domain, solution);
      }
    }

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j] <<
					(j + 1 != result[i].size() ? ' ' : '\n');
			}
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
