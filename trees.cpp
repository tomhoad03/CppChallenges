#include <iostream>

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
        treeWalk(root);
        cout << endl;
    }

    void treeWalk(struct Node* node) {
        struct Node* left = node -> getLeftChild();
            
        if (left != NULL) {
            treeWalk(left);
        }
        node -> printValue();

        struct Node* right = node -> getRightChild();
            
        if (right != NULL) {
            treeWalk(right);
        }
    }
};

int main() {
    struct Tree* tree = new Tree(5);

    tree -> newNode(3);
    tree -> treeWalk();

    return 0;
}