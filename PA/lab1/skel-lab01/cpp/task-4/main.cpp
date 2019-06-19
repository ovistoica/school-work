#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(fast_pow(base, exponent, mod));
	}

private:
	int base, exponent, mod;

	void read_input() {
		ifstream fin("in");
		fin >> base >> exponent >> mod;
		fin.close();
	}

	int just_pow (int base, int exponent) {
	}


	int fast_pow(int base, int exponent, int mod) {
		if (exponent == 1) {
			return base;
		}
		else if (exponent == 0) {
			return 1;
		}
		else if(exponent % 2 == 0) {
			int tmp = fast_pow(base, exponent / 2, mod);
			return (1LL * (tmp %mod) * (tmp %mod)) % mod;
		}
		else {
			int tmp = fast_pow(base, (exponent - 1), mod);
			return (1LL *(base % mod) * (tmp % mod)) % mod;
		}
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
