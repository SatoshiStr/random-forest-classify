#include <iostream>

#include <set>
#include <map>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stack>
using namespace std;

#include "lib.h"
const double loge2 = log(2);

inline bool get_data_attr(const set<short> data, int index) {
    if(data.find(index) != data.end()) {
        return 1;
    } else {
        return 0;
    }
}

// double get_info_entropy(const set<short> (&datas)[DATA_SUM], 
//     const map<short, bool> &preCondition, const char *labels) {
//     //
//     int a_cnt = 0, b_cnt = 0;
//     double sum_cnt;
//     for(int i = 0; i < DATA_SUM; ++i) {
//         bool inRange = true;
//         const set<short> &data = datas[i];
//         for(const auto &cond : preCondition) {
//             if(get_data_attr(data, cond.first) != cond.second) {
//                 inRange = false;
//                 break;
//             }
//         }
//         if(inRange) {
//             if(labels[i] == 0) {
//                 ++a_cnt;
//             } else {
//                 ++b_cnt;
//             }
//             cout << "inrange: " << i << endl;
//         }
//     }
//     sum_cnt = a_cnt + b_cnt;
//     if(int(sum_cnt) == 0) {
//         cout << "empty sum error" << endl;
//         return 1;
//     }
//     double rate1 = a_cnt / sum_cnt, rate2 = 1 - rate1;
//     double entropy;
//     if(a_cnt == 0 || b_cnt == 0) {
//         entropy = 0;
//     } else {
//         entropy = - (rate1 * log(rate1) / loge2 + rate2 * log(rate2) / loge2);
//     }
//     return entropy;
// }

double get_sep_info_entropy(const set<short> (&datas)[DATA_SUM], 
    const map<short, bool> &preCondition, const char *labels, int sepIndex) {
    //
    int a_cnt = 0, b_cnt = 0, y_cnt = 0, z_cnt = 0;
    int grp1_cnt, grp2_cnt;
    for(int i = 0; i < DATA_SUM; ++i) {
        bool inRange = true;
        const set<short> &data = datas[i];
        for(const auto &cond : preCondition) {
            if(get_data_attr(data, cond.first) != cond.second) {
                inRange = false;
                break;
            }
        }
        if(inRange) {
            if(get_data_attr(data, sepIndex) == 0) {
                if(labels[i] == 0) {
                    ++a_cnt;
                } else {
                    ++b_cnt;
                }
            } else {
                if(labels[i] == 0) {
                    ++y_cnt;
                } else {
                    ++z_cnt;
                }
            }
            // cout << "inrange-index: " << i << endl;
        }
    }
    // cout << "a b y z : "
    //     << a_cnt << " " << b_cnt << " " << y_cnt << " " << z_cnt << endl; 
    double entropy, ent1, ent2;
    double grp1_rate, grp2_rate;
    double rate1, rate2;
    grp1_cnt = a_cnt + b_cnt;
    grp2_cnt = y_cnt + z_cnt;
    grp1_rate = grp1_cnt / double(grp1_cnt + grp2_cnt);
    grp2_rate = 1 - grp1_rate;
    if(grp1_cnt == 0) {
        ent1 = 0;
    } else {
        // grp1 entropy
        rate1 = a_cnt / double(grp1_cnt);
        rate2 = 1 - rate1;
        if(a_cnt == 0 || b_cnt == 0) {
            ent1 = 0;
        } else {
            ent1 = - (rate1 * log(rate1) / loge2 + rate2 * log(rate2) / loge2);
        }
        // cout << "ent1 " << ent1 << endl;
    }
    if(grp2_cnt == 0) {
        ent2 = 0;
    } else {
        rate1 = y_cnt / double(grp2_cnt);
        rate2 = 1 - rate1;
        // cout << "rate1, 2 : " << rate1 << " " << rate2 << endl;
        if(y_cnt == 0 || z_cnt == 0) {
            ent2 = 0;
        } else {
            ent2 = - (rate1 * log(rate1) / loge2 + rate2 * log(rate2) / loge2);
        }
        // cout << "ent2 " << ent2 << endl;
    }
    entropy = grp1_rate * ent1 + grp2_rate * ent2;
    return entropy;
}

struct Item {
    Node *node;
    set<short> avaiIndex;
    map<short, bool> preCond;
    Item() {}
    Item(Node *nodePtr, set<short> _avaiIndex, map<short, bool> _preCond = map<short, bool>()) {
        avaiIndex = _avaiIndex;
        preCond = _preCond;
        node = nodePtr;
    }
};

Node * make_decision_tree(const set<short> (&datas)[DATA_SUM], const char *labels) {
    const int ALL_ARG_SUM = 4;
    const int ARG_SUM = 3;
    // Generate ARG_SUM different index in range(0, ALL_ARG_SUM)
    set<short> arg_set;
    short rand_index;
    //
    srand(time(NULL));
    while(arg_set.size() != ARG_SUM) {
        rand_index = rand() % ALL_ARG_SUM;
        if(arg_set.find(rand_index) == arg_set.end()) {
            arg_set.insert(rand_index);
            cout << "arg_set: " << rand_index << endl;
        }
    }
    //
    Node *tree;
    stack<Item *> stk;
    map<short, bool> preCondition;
    double min_ent_val = 1000, tmp_ent;
    int min_index = -1;
    // Init first node;
    for(const auto &index : arg_set) {
        tmp_ent = get_sep_info_entropy(datas, preCondition, labels, index);
        if(tmp_ent < min_ent_val) {
            min_ent_val = tmp_ent;
            min_index = index;
        }
    }
    tree = new Node(min_index);
    arg_set.erase(min_index);
    stk.push(Item(tree, arg_set));
    // Depth first. make tree.
    Item top;
    while(stk.size()) {
        top = stk.top();
        stk.pop();

    }
}

void testInfoEntropy() {
    set<short> datas[DATA_SUM];
    //
    set<short> a;
    a.insert(1);
    a.insert(3);
    datas[0] = a;
    //
    set<short> b;
    b.insert(0);
    b.insert(1);
    b.insert(2);
    datas[1] = b;
    //
    set<short> c;
    c.insert(0);
    c.insert(2);
    datas[2] = c;
    //
    set<short> d;
    d.insert(1);
    d.insert(2);
    datas[3] = d;
    //
    map<short, bool> preCondition;
    preCondition[2] = 1;
    // preCondition[3] = 0;
    char labels[DATA_SUM] = {1, 1, 0, 1};
    cout << get_sep_info_entropy(datas, preCondition, labels, 3) << endl;
}