#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Object {
	int weight;
	int price;

	Object(int _weight, int _price) : weight(_weight), price(_price) {}
};

bool compare(Object& ob1, Object& ob2)
{
	return 1.0 * (ob1.price / ob1.weight) >= 1.0 * (ob2.price / ob2.weight);
}

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, w;
	vector<Object> objs;

	void read_input() {
		ifstream fin("in");
		fin >> n >> w;
		for (int i = 0, weight, price; i < n; i++) {
			fin >> weight >> price;
			objs.push_back(Object(weight, price));
		}
		fin.close();
	}

	double get_result() {
		/*
		TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
		*/
		double total_cost = 0.0;
		sort(objs.begin(), objs.end(),compare); 
		for(Object obj : objs) {
			if(w == 0) {
				break;
			}
			if(w - obj.weight >= 0) {
				total_cost += (double)obj.price;
				w -= obj.weight;
			} else {
				total_cost += 1.0 * w * (obj.price / obj.weight);
			}
		}
		return total_cost;
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
