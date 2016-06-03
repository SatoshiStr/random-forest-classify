#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

/*
* statistic arg distribution of train-data
*/

void arg_per() {
    ifstream train_ifs("train.txt");
    string line;
    int arr[11392+1] = {0};
    while(getline(train_ifs, line)) {
        int len = line.length();
        int left = 0, right = line.find(' ');
        int index;
        left = right + 1;
        while(left < len) {
            right = line.find(':', left);
            index = stoi(line.substr(left, right - left));
            arr[index]++;
            left = right + 1;
            right = line.find(' ', left);
            if(right == string::npos)
                break;
            left = right + 1;
        }
    }
    ofstream statis_ofs("arg_per.txt");
    for(int i = 0; i < 11393; ++i) {
        statis_ofs << arr[i] << " ";
    }
}

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