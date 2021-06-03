#include <iostream>

using namespace std;

struct Node {
    int key;
    int value;
    struct Node* leftChild;
    struct Node* rightChild;

    Node(int k) {
        key = k;
        value = 0;
        leftChild = NULL;
        rightChild = NULL;
    }

    Node(int k, int v) {
        key = k;
        value = v;
        leftChild = NULL;
        rightChild = NULL;
    }

    void getKey() {
        cout << key << endl;
    }

    void getValue() {
        cout << value << endl;
    }
    void setValue(int v) {
        value = v;
    }

    Node* getLeftChild() {
        return leftChild;
    }
    Node* getRightChild() {
        return leftChild;
    }

    void addLeftChild(Node* l) {
        leftChild = l;
    }
    void addRightChild(Node* r) {
        rightChild = r;
    }
};

struct Tree {
    struct Node* root = new Node(1);
    int key = 1;

    void createBasic() {
        root -> setValue(5);
        root -> addLeftChild(new Node(2, 3));
        root -> addRightChild(new Node(3, 10));
    }

    void getNode(int n) {
        if (n == 1) {
            root -> getValue();
        }
    }

    void setNode(int n, int v) {
        if (n == 1) {
            root -> setValue(v);
        }
    }

    void treeWalk() {
        treeWalk(root);
    }

    void treeWalk(struct Node* node) {
        struct Node* left = node -> getLeftChild();
            
        if (left != NULL) {
            treeWalk(left);
        }
        node -> getValue();

        struct Node* right = node -> getRightChild();
            
        if (right != NULL) {
            treeWalk(right);
        }
    }
};

int main() {
    struct Tree* tree = new Tree();
    tree -> createBasic();
    tree -> treeWalk();

    return 0;
}