#include <iostream>

using namespace std;

struct Node
{
    int key;
    struct Node* leftChild;
    struct Node* rightChild;

    Node(int k) {
        key = k;
        leftChild = NULL;
        rightChild = NULL;
    }

    int getKey() {
        cout << key << endl;
        return key;
    }

    Node* getLeftChild() {
        cout << leftChild -> key << endl;
        return leftChild;
    }
    Node* getRightChild() {
        cout << rightChild -> key << endl;
        return leftChild;
    }

    void newLeftChild() {
        leftChild = new Node(key + 1);
    }
    void newRightChild() {
        leftChild = new Node(key + 2);
    }

    void addLeftChild(Node* l) {
        leftChild = l;
    }
    void addRightChild(Node* r) {
        rightChild = r;
    }
};

int main() {
    struct Node* root = new Node(1);
    root -> getKey();
    root -> newLeftChild();
    root -> getLeftChild() -> newLeftChild();
    root -> getLeftChild() -> getLeftChild();
    
    return 0;
}