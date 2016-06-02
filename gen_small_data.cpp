#include <fstream>
#include <iostream>
using namespace std;

void make_small_data() {
    // generate small data text file
    ifstream train_ifs("train.txt");
    ofstream small_ofs("10w.txt");
    string line;
    int sum = 100000, cnt = 0;
    while(getline(train_ifs, line) && cnt < sum) {
        small_ofs << line << endl;
        ++cnt;
        cout << " cnt : " << cnt << endl;
    }
}

int main() {
	make_small_data();
}