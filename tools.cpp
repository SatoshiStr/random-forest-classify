#include <iostream>
#include <fstream>
using namespace std;

//const char * train_file = "train.txt";
const char * train_file = "small.txt";

void make_small_data() {
    // generate small data text file
    ifstream train_ifs("train.txt");
    ofstream small_ofs("nano.txt");
    string line;
    int sum = 100, cnt = 0;
    while(getline(train_ifs, line) && cnt < sum) {
        small_ofs << line << endl;
        ++cnt;
        cout << " cnt : " << cnt << endl;
    }
}

bool make_data() {
    /*
    save features in array. each feature is a bool value.
    save lables in lables array.
    */
    ifstream train_ifs(train_file);
    string line;
    
    while(getline(train_ifs, line)) {
        int len = line.length();
        int left = 0, right = line.find(' ');
        bool label = stoi(line.substr(0, right));
        int index, value;
        left = right + 1;
        while(left < len) {
            right = line.find(':', left);
//          index = stoi(line.substr(left, right - left));
            left = right + 1;
            right = line.find(' ', left);
            value = stoi(line.substr(left, right - left));
//          cout << index  << " " << value << endl;
            if(right == string::npos)
                break;
            left = right + 1;
        }
    }
}

bool check_data() {
    // return 1 if all feature values are 0 or 1.
    // otherwise return 0.
    ifstream train_ifs(train_file);
    string line;
    int line_cnt = 0;
    
    while(getline(train_ifs, line)) {
//        cout << line << endl;
        line_cnt++;
//        return 1;
        int len = line.length();
        int left = 0, right = line.find(' ');
        bool label = stoi(line.substr(0, right));
        int index, value;
        left = right + 1;
        while(left < len) {
            right = line.find(':', left);
//            index = stoi(line.substr(left, right - left));
            left = right + 1;
            right = line.find(' ', left);
            value = stoi(line.substr(left, right - left));
            if(value != 0 && value != 1) {
                cout << "error" << endl << " line " << line_cnt << endl;
                return 0;
            }
//            cout << index  << " " << value << endl;
            if(right == string::npos)
                break;
            left = right + 1;
        }
    }
    cout << " line: succ " << line_cnt << endl;
}

