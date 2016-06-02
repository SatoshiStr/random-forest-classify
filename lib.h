#include <set>
#include <map>
// const int DATA_SUM = 10000; //2177020
const int DATA_SUM = 100000;//2177020;
const int TEST_SUM = 220245;
// tools
void make_small_data();
bool check_data();
void arg_per();
void make_data(std::set<short> (&datas)[DATA_SUM], bool (&labels)[DATA_SUM]);
void make_test_set(std::set<short> (&test_set)[TEST_SUM],
    std::pair<int, bool>(&outputs)[TEST_SUM]);
void make_output(std::pair<int, bool>(&outputs)[TEST_SUM]);

// decision tree
// type of Node
const char NODE = 1, LEAF = 2;
struct Node {
    short value;
    // For type = NODE, value is index of attribute;
    // For type = LEAF, value is label.
    
    Node *left;
    Node *right;
    Node() {}
    Node(short _value, Node *_left = NULL, Node *_right = NULL) {
        //
        value = _value;

        left = _left;
        right = _right;
    }
};

Node * make_decision_tree(const std::set<short> (&datas)[DATA_SUM], const bool *labels);
void predict_test_set(std::set<short> (&test_set)[TEST_SUM],
    std::pair<int, bool>(&outputs)[TEST_SUM], Node **ptr, int len);
void print_tree(Node * tree, int pad=0);
void testInfoEntropy();
void testMakeTree();
