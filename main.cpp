#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>

#include "lib.h"
#include <time.h>
using namespace std;




set<short> datas[DATA_SUM] = {};
bool labels[DATA_SUM] = {};
set<short> test_set[TEST_SUM] = {};
pair<int, bool> outputs[TEST_SUM] = {};

int main() {
    // make_small_data();
    // testInfoEntropy();
    cout << "run" << endl;
    // arg_per();
    const int TREE_SUM = 1;
    Node * treeArr[TREE_SUM];
    make_data(datas, labels);
    int start = time(0);
    for(int i = 0; i < TREE_SUM; ++i) {
        treeArr[i] = make_decision_tree(datas, labels);
        print_tree(treeArr[i]);
        int f = time(0);
        cout << "pass " << f - start << " tree " << i+1
          << " ave " << double(f-start) / (i+1) << endl;
    }
    cout << "test" << endl;
    make_test_set(test_set, outputs);
    predict_test_set(test_set, outputs, treeArr, 1);
    make_output(outputs);
    return 0;
} 

//



