#include <set>
#include <map>
const int DATA_SUM = 4;//100; //2177020

// tools
void make_small_data();
bool check_data();

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
void testInfoEntropy();

