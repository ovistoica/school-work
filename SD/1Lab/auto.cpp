#include <iostream>
#include <fstream>

int main() {

	/*
	* Use out as std::cout
	* ex : out << var1 << " " << var2 << std::endl;
	*/

#ifdef DEBUG
	std::ostream& out = std::cout;
#else
	std::ofstream file;
	file.open("Out/Lab1/task1.out");
	std::ostream& out = file;
#endif

	std::pair<int, float> arr[10];
	auto sum = 0.0;

	for(auto i = 0; i < 10; i++) {
		arr[i].first = i;
		arr[i].second = 2.5 * i;
	}

	for(auto i : arr) {
		out << i.first << " ";
		sum += i.second;
	}
	out << sum << std::endl;

	/*
	 * TODO Create array of pair, print the first field of each and the sum of all second fields
	 */

	return 0;
}
