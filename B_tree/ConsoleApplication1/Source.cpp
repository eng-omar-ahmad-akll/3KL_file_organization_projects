#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;


class BTreeNode {
public:
    char* keys;
    BTreeNode** children;
    int numKeys;
    bool isLeaf;
    int maxKeys;

    BTreeNode(bool leaf, int maxKeys) : isLeaf(leaf), maxKeys(maxKeys), numKeys(0) {
        keys = new char[maxKeys + 1];
        children = new BTreeNode * [maxKeys + 2];
        memset(children, 0, sizeof(BTreeNode*) * (maxKeys + 2));
    }

    void insertNonFull(char k);
    void splitChild(int i, BTreeNode* y);
    void printTreePretty(string indent = "");
};

class BTree {
public:
    BTreeNode* root;
    int maxKeys;

    BTree(int order) : root(nullptr), maxKeys(order) {}

    void insert(char k);
    void printPretty();
};

void BTree::insert(char k) {
    if (!root) {
        root = new BTreeNode(true, maxKeys);
        root->keys[0] = k;
        root->numKeys = 1;
    }
    else {
        if (root->numKeys == maxKeys) {
            BTreeNode* s = new BTreeNode(false, maxKeys);
            s->children[0] = root;
            s->splitChild(0, root);
            int i = (s->keys[0] < k) ? 1 : 0;
            s->children[i]->insertNonFull(k);
            root = s;
        }
        else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(char k) {
    int i = numKeys - 1;

    if (isLeaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        numKeys++;
    }
    else {
        while (i >= 0 && keys[i] > k)
            i--;
        i++;

        if (children[i]->numKeys == maxKeys) {
            splitChild(i, children[i]);
            if (keys[i] < k) i++;
        }
        children[i]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    int t = maxKeys / 2;
    BTreeNode* z = new BTreeNode(y->isLeaf, maxKeys);

    for (int j = 0; j < maxKeys - t - 1; j++)
        z->keys[j] = y->keys[j + t + 1];

    if (!y->isLeaf) {
        for (int j = 0; j < maxKeys - t; j++)
            z->children[j] = y->children[j + t + 1];
    }

    z->numKeys = maxKeys - t - 1;
    y->numKeys = t;

    for (int j = numKeys; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = numKeys - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t];
    numKeys++;
}

void BTreeNode::printTreePretty(string indent) {
    for (int i = 0; i < numKeys; i++) {
        if (!isLeaf) children[i]->printTreePretty(indent + "    ");
        if (i == 0) cout << indent;
        cout << keys[i];
        if (i < numKeys - 1) cout << " ";
    }
    cout << endl;
    if (!isLeaf) children[numKeys]->printTreePretty(indent + "    ");
}

void BTree::printPretty() {
    if (root)
        root->printTreePretty();
}

int main() {
    int order;
    cout << "Enter the maximum number of keys per node (order): ";
    cin >> order;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter the elements (letters or digits): ";
    BTree tree(order);

    for (int i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        if (!temp.empty()) {
            tree.insert(temp[0]); 
        }
    }

    cout << "\nTree Visualization:\n\n";
    tree.printPretty();

    return 0;
}
