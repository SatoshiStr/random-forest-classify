#include <iostream>
#include <fstream>
#include <set>
#include "lib.h"
using namespace std;

const char * train_file = "train.txt";
void make_data(set<short> (&datas)[DATA_SUM], bool (&labels)[DATA_SUM]) {
    /*
    save features with 1 in set. each feature is a bool value.
    save lables in lables array.
    */
    ifstream train_ifs(train_file);
    string line;
    
    int i = 0;
    int zero_cnt = 0, one_cnt = 0;
    while(getline(train_ifs, line) && i < DATA_SUM) {
        int len = line.length();
        int left = 0, right = line.find(' ');
        bool label = stoi(line.substr(0, right));
        labels[i] = label;
        int index, value;
        set<short> data;
        left = right + 1;
        while(left < len) {
            right = line.find(':', left);
            index = stoi(line.substr(left, right - left));
            datas[i].insert(index);
            left = right + 1;
            right = line.find(' ', left);
            // value = stoi(line.substr(left, right - left));
            // cout << index  << " " << value << endl;
            if(right == string::npos)
                break;
            left = right + 1;
        }
        i++;
    }
    // cout << "zero, one:  " << zero_cnt << " " << one_cnt << endl;
    // cout << "0 percentage:  " << zero_cnt / double(zero_cnt + one_cnt) << endl;
    // for(const auto &data : datas) {
    //     for(const auto &item : data) {
    //         cout << item << " ";
    //     }
    //     cout << endl;
    // }
    
    // for(const auto &lab : labels) {
    //     cout << lab << endl;
    // }
    cout << " data size " << i << endl;
}

void make_test_set(set<short> (&test_set)[TEST_SUM],
    pair<int, bool>(&outputs)[TEST_SUM]) {
    ifstream test_ifs("test.txt");
    string line;
    
    int i = 0;
    while(getline(test_ifs, line)) {
        int len = line.length();
        int left = 0, right = line.find(' ');
        int id = stoi(line.substr(0, right));
        outputs[i].first = id;
        int index, value;
        set<short> data;
        left = right + 1;
        while(left < len) {
            right = line.find(':', left);
            index = stoi(line.substr(left, right - left));
            test_set[i].insert(index);
            left = right + 1;
            right = line.find(' ', left);
            // value = stoi(line.substr(left, right - left));
            // cout << index  << " " << value << endl;
            if(right == string::npos)
                break;
            left = right + 1;
        }
        i++;
    }
    // for(const auto &data : test_set) {
    //     for(const auto &item : data) {
    //         cout << item << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "test size " << i << endl;
}

void make_output(pair<int, bool>(&outputs)[TEST_SUM]) {
    ofstream output_ofs("output.txt");
    output_ofs << "id,label" << endl;
    for(const auto &item : outputs) {
        output_ofs << item.first << "," << item.second << endl;
    }
}


