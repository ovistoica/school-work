#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(compute_sqrt());
	}

private:
	double n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	double compute_sqrt() {
		/*
		TODO: Calculati sqrt(n) cu o precizie de 0.001
		Precizie de 10^-x = |rezultatul vostru - rezultatul corect| <= 10^-x
		*/
		double start, end, mid;

		if (n < 1) {
			start = 0.1;
			end = 0.999;
		} else {
			start = 1;
			end = n / 2;
		}

		while(end > start) {
			mid = (start + end) / 2;
			if(fabs(n - (mid * mid) <= 0.001)) {
				return mid;
			}
			else if(mid * mid < n) {
				start = mid;
			} else {
				end = mid;
			}
		}
	}

	void print_output(double result) {
		ofstream fout("out");
		fout << setprecision(4) << fixed << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
