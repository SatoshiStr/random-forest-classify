#include <iostream>

#include <set>
#include <map>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stack>
using namespace std;

#include "lib.h"
const int ARG_SUM = 6;
const double loge2 = log(2);

inline bool get_data_attr(const set<short> data, int index) {
    if(data.find(index) != data.end()) {
        return 1;
    } else {
        return 0;
    }
}


inline pair<int, int> cal_label(const set<short> (&datas)[DATA_SUM],
    const map<short, bool> &preCondition, const bool *labels) {
    int a_cnt = 0, b_cnt = 0;
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
            if(labels[i] == 0) {
                ++a_cnt;
            } else {
                ++b_cnt;
            }
        }
    }
    return pair<int, int>{a_cnt, b_cnt};
}

pair<double,int> get_sep_info_entropy(const set<short> (&datas)[DATA_SUM], 
    const map<short, bool> &preCondition, const bool *labels, int sepIndex) {
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
    cout << "a b y z : "
        << a_cnt << " " << b_cnt << " " << y_cnt << " " << z_cnt << endl; 
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
    int label = -1;
    if(a_cnt + y_cnt == 0) {
        label = 1;
    } else if(b_cnt + z_cnt == 0) {
        label = 0;
    }
    return pair<double, int>{entropy, label};
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
const int ALL_ARG_SUM = 56;

int arg_array[ALL_ARG_SUM] = {45, 203, 204, 521, 542, 543, 544, 577, 1594, 1595, 1601,
    1602, 1614, 2019, 2020, 2024, 2026, 2037, 2038, 2039, 2040, 2044, 2054, 2082,
    2084, 2192, 2193, 2198, 2199, 2210, 2211, 2224, 2225, 2228, 2229, 2230, 2231,
    2236, 2237, 9011, 9153, 10171, 10172, 11179, 11223, 11235,
    11236, 11259, 11260, 11262, 11282, 11296, 11297, 11377, 11386, 11390};

Node * make_decision_tree(const set<short> (&datas)[DATA_SUM], const bool *labels) {
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
    // arg_set.insert(0);
    // arg_set.insert(2);
    // arg_set.insert(3);
    //
    Node *tree;
    stack<Item> stk;
    pair<double, int> tmpPair;
    double min_ent_val = 1000, tmp_ent;
    int min_index = -1, min_label;
    // Init first node;
    tree = new Node(-1);
    stk.push(Item(tree, arg_set));
    // Depth first. make tree.
    Item top;
    while(stk.size()) {
        top = stk.top();
        cout << top.node->value << " xx" << endl;
        stk.pop();
        set<short> &avaiIndex = top.avaiIndex;
        if(avaiIndex.size() == 0) {
            // no any more available index. 
            // Set current node as leaf with label which is more than another.
            pair<int, int> cntPair = cal_label(datas, top.preCond, labels);
            cout << "0, 1:  " << cntPair.first << " " << cntPair.second << endl;
            if(cntPair.first > cntPair.second) {
                top.node->value = 0;
            } else if(cntPair.first > cntPair.second) {
                top.node->value = rand() % 2;
            } else {
                top.node->value = 1;
            }
        } else {
            min_ent_val = 1000;
            for(const auto &index : avaiIndex) {
                tmpPair = get_sep_info_entropy(datas, top.preCond, labels, index);
                if(tmpPair.first < min_ent_val) {
                    min_ent_val = tmpPair.first;
                    min_index = index;
                    min_label = tmpPair.second;
                }
            }
            cout << "min index, ent, label " << min_index << " " << min_ent_val
                << " " << min_label << endl; 
            if(min_ent_val > 999.9) {
                // empty
                top.node->value = 0;
            } else if(min_label != -1) {
                // all labels are the same. Set current node as leaf.
                top.node->value = min_label;
            } else {
                top.node->value = min_index;
                Node *leftPtr, *rightPtr;
                leftPtr = new Node(-1);
                rightPtr = new Node(-1);
                top.node->left = leftPtr;
                top.node->right = rightPtr;
                map<short, bool> aCond(top.preCond), bCond(aCond);
                aCond[top.node->value] = 0;
                bCond[top.node->value] = 1;
                avaiIndex.erase(top.node->value);
                Item aItem = Item(leftPtr, avaiIndex, aCond);
                Item bItem = Item(rightPtr, avaiIndex, bCond);
                stk.push(bItem);
                stk.push(aItem);
            }
        }
    }
    return tree;
}

inline bool get_predict_label(Node *tree, set<short> data) {
    while(tree) {
        // cout << "tree " << (long long)(tree) << endl;
        if(tree->left == NULL && tree->right == NULL) {
            return tree->value;
        } else {
            if(get_data_attr(data, tree->value) == 0) {
                tree = tree->left;
            } else {
                tree = tree->right;
            }
        }
    }
}

void predict_test_set(set<short> (&test_set)[TEST_SUM],
    pair<int, bool>(&outputs)[TEST_SUM], Node **ptr, int len) {
    for(int i = 0; i < TEST_SUM; ++i) {
        int a_cnt = 0, b_cnt = 0;
        for(int j = 0; j < len; ++j) {
            // cout << "predict " << i << "  " << j << endl;
            if(get_predict_label(ptr[j], test_set[i]) == 0) {
                ++a_cnt;
            } else {
                ++b_cnt;
            }
        }
        if(a_cnt >= b_cnt) {
            outputs[i].second = 0;
        } else {
            outputs[i].second = 1;
        }
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
    bool labels[DATA_SUM] = {1, 1, 0, 1};
    cout << get_sep_info_entropy(datas, preCondition, labels, 3).first << endl;
}
void pd(int pad) {
    for(int i = 0; i < pad; ++i) {
        cout << "    ";
    }
}
void print_tree(Node * tree, int pad) {
    pd(pad);
    cout << tree->value;
    if (tree->left || tree->right) {
        cout << " {" << endl;
    } else {
        cout << " ." << endl;
    }
    if(tree->left)
        print_tree(tree->left, pad+1);
    if(tree->right)
        print_tree(tree->right, pad+1);
    
    if (tree->left || tree->right) {
        pd(pad);
        cout << "}" << endl;
    }
}
void testMakeTree() {
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
    // map<short, bool> preCondition;
    // preCondition[2] = 1;
    // preCondition[3] = 0;
    bool labels[DATA_SUM] = {1, 1, 0, 1};
    Node * tree = make_decision_tree(datas, labels);
    print_tree(tree);
}
void test2() {

}
