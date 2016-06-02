#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

void see_per(vector<int> vec) {
	sort(vec.begin(), vec.end());
	for(int i = vec.size() -1; i >= 0; --i) {
		int item = vec[i];
		cout << item << "\t" << item / 2177020.0 << endl;
	}
}

int main() {
	// read
	ifstream ifs("arg_per.txt");
	int num;
	vector<int> vec;
	while(ifs >> num) {
		vec.push_back(num);
	}
	cout << "vec size " << vec.size() << endl;
	//
	ofstream ofs("better_arg.txt");
	const double RANGE = 0.7, LOWER = (1 - RANGE) / 2, HIGH = 1 - LOWER;
	int cnt = 0;
	cout << "low high " << LOWER << " " << HIGH << endl;
	for(int i = 0; i < vec.size(); ++i) {
		if(vec[i] > 2177020 * LOWER && vec[i] < 2177020 * HIGH) {
			++cnt;
			ofs << i << " ";
		}
	}
	cout << cnt << endl;
	return 0;
}