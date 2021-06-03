#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    struct Node* leftChild;
    struct Node* rightChild;

    Node(int v) {
        value = v;
        leftChild = NULL;
        rightChild = NULL;
    }

    void printValue() {
        cout << value << " ";
    }
    int getValue() {
        return value;
    }
    void setValue(int v) {
        value = v;
    }

    Node* getLeftChild() {
        return leftChild;
    }
    Node* getRightChild() {
        return rightChild;
    }

    void addLeftChild(Node* l) {
        leftChild = l;
    }
    void addRightChild(Node* r) {
        rightChild = r;
    }
};

struct Tree {
    struct Node* root;

    Tree(int v) : root(new Node(v)) { };

    void newNode(int v) {
        newNode(root, v);
    }

    void newNode(struct Node* node, int v1) {
        int v2 = node -> getValue();

        if (v1 < v2) {
            if (node -> getLeftChild() != NULL) {
                newNode(node -> getLeftChild(), v1);
            } else {
                node -> addLeftChild(new Node(v1));
            }
        } else if (v1 > v2) {
            if (node -> getRightChild() != NULL) {
                newNode(node -> getRightChild(), v1);
            } else {
                node -> addRightChild(new Node(v1));
            }
        } else {
            cout << "Node already exists!" << endl;
        }
    }

    void treeWalk() {
        std::vector<int> values = {};
        values = treeWalk(root);
        cout << values[1] << endl;
    }

    std::vector<int> treeWalk(struct Node* node) {
        struct Node* left = node -> getLeftChild();
        struct Node* right = node -> getRightChild();

        std::vector<int> leftValues = {}, rightValues = {}, mergeValues = {};
        int value = node -> getValue();
            
        if (left != NULL) {
            leftValues = treeWalk(left);
        }
        if (right != NULL) {
            rightValues = treeWalk(right);
        }

        int leftSize = sizeof(leftValues) / sizeof(leftValues[0]);
        int rightSize = sizeof(rightValues) / sizeof(rightValues[0]);

        cout << rightSize;

        for (int i = 0; i < leftSize - 1; i++) {
            mergeValues[i] = leftValues[i];
        }

        mergeValues[leftSize] = value;

        for (int i = leftSize + 1; i < leftSize + rightSize; i++) {
            mergeValues[i] = leftValues[i - leftSize];
        }
        return mergeValues;
    }
};

int main() {
    struct Tree* tree = new Tree(5);

    tree -> newNode(3);
    tree -> treeWalk();

    return 0;
}