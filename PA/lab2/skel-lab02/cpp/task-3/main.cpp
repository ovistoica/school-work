#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Homework {
	int deadline;
	int score;

	Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

struct greaterByScore
{
	bool operator() (const Homework& h1, const Homework& h2) const 
	{
		return h1.score >= h2.score;
	}
};


class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<Homework> hws;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, deadline, score; i < n; i++) {
			fin >> deadline >> score;
			hws.push_back(Homework(deadline, score));
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Aflati punctajul maxim pe care il puteti obtine planificand
		optim temele.
		*/
		int total_score, curr_week;
		curr_week = hws.at(hws.size() - 1).deadline;
		priority_queue<Homework, vector<Homework>, greaterByScore> maxHeap;
		for(size_t i = hws.size() - 1; i >= 0; --i) {
			if(hws.at(i).deadline == curr_week) {
				maxHeap.push(hws.at(i));
			}
			else if (hws.at(i).deadline < curr_week) {
				--curr_week;
				if(maxHeap.empty()) {
					total_score += hws.at(i).score;
				} else {
					if(hws.at(i).score > maxHeap.top().score) {
						total_score += hws.at(i).score;
					} else {
						total_score += maxHeap.top().score;
						maxHeap.pop();
						maxHeap.push(hws.at(i));
					}
				}
			}
		}
		return total_score;
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
