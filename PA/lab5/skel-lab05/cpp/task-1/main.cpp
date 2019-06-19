#include <iostream>
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
	int n, k;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin.close();
	}

	vector<vector<int> > get_result() {
		vector<vector<int> > all;
		/*
		TODO: Construiti toate aranjamentele de N luate cate K ale
		multimii {1, ..., N}.

		Pentru a adauga un nou aranjament:
			vector<int> aranjament;
			all.push_back(aranjament);
		*/
    std::vector<int> domain(n), solution(k);
    for (int i = 0; i < n; ++i) {
        domain[i] = i + 1;
    }

    back(domain, solution, all);

		return all;
	}

  void back(std::vector<int> &domain,
    std::vector<int> &solution, std::vector<std::vector<int>> &all){

    if(domain.size() == n - k){
      all.push_back(solution);
      return;
    }
    for (unsigned int i = 0; i < domain.size(); ++i) {
        /* retinem valoarea pe care o scoatem din domeniu ca sa o readaugam dupa
        apelarea recursiva a backtracking-ului */
        int tmp = domain[i];

        /* adaug elementul curent la potentiala solutie */
        solution.push_back(domain[i]);
        /* sterg elementul curent din domeniu ca sa il pot pasa prin referinta
        si sa nu fie nevoie sa creez alt domeniu */
        domain.erase(domain.begin() + i);

        /* apelez recursiv backtracking pe domeniul si solutia modificate */
        back(domain, solution, all);

        /* refac domeniul si solutia la modul in care aratau inainte de apelarea
        recursiva a backtracking-ului, adica readaug elementul eliminat in
        domeniu si il sterg din solutie */
        domain.insert(domain.begin() + i, tmp);
        solution.pop_back();
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
