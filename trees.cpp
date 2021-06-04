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

    void setLeftChild(Node* l) {
        leftChild = l;
    }
    void setLeftChild() {
        leftChild = NULL;
    }
    void setRightChild(Node* r) {
        rightChild = r;
    }
    void setRightChild() {
        rightChild = NULL;
    }
};

struct Tree {
    struct Node* root;

    Tree(int v) : root(new Node(v)) { };

    void addNode(int v) {
        addNode(root, v);
    }

    void addNode(struct Node* node, int v1) {
        struct Node* left = node -> getLeftChild();
        struct Node* right = node -> getRightChild();
        int v2 = node -> getValue();

        if (v1 < v2) {
            if (left != NULL) {
                addNode(left, v1);
            } else {
                node -> setLeftChild(new Node(v1));
            }
        } else if (v1 > v2) {
            if (right != NULL) {
                addNode(right, v1);
            } else {
                node -> setRightChild(new Node(v1));
            }
        } else {
            cout << "Node already exists!" << endl;
        }
    }

    void removeNode(int v) {
        removeNode(root, NULL, v);
    }

    void removeNode(struct Node* node, struct Node* parentNode, int v1) {
        struct Node* left = node -> getLeftChild();
        struct Node* right = node -> getRightChild();
        int v2 = node -> getValue();

        if (v1 == v2) {
            if (left != NULL) {
                struct Node* currentRight = left;
                struct Node* lastRight = NULL;

                while (currentRight -> getRightChild() != NULL) {
                    lastRight = currentRight;
                    currentRight = currentRight -> getRightChild();
                }
                node -> setValue(currentRight -> getValue());
                node -> setLeftChild(left);
                node -> setRightChild(right);

                removeNode(node -> getLeftChild(), node, node -> getValue());
            } else if (right != NULL) {
                struct Node* currentLeft = right;
                struct Node* lastLeft = NULL;

                while (currentLeft -> getLeftChild() != NULL) {
                    lastLeft = currentLeft;
                    currentLeft = currentLeft -> getLeftChild();
                }
                node -> setValue(currentLeft -> getValue());
                node -> setLeftChild(left);
                node -> setRightChild(right);

                removeNode(node -> getRightChild(), node, node -> getValue());
            } else if (left == NULL && right == NULL) {
                if (parentNode -> getLeftChild() != NULL && parentNode -> getLeftChild() -> getValue() == v1) {
                    parentNode -> setLeftChild();
                } else {
                    parentNode -> setRightChild();
                }
            }
        } else if (v1 < v2) {
            removeNode(left, node, v1); 
        } else if (v1 > v2) {
            removeNode(right, node, v1);
        }
    }

    void treeWalk() {
        string values = treeWalk(root);
        cout << values << endl;
    }

    string treeWalk(struct Node* node) {
        struct Node* left = node -> getLeftChild();
        struct Node* right = node -> getRightChild();

        string leftValues, rightValues, value = to_string(node -> getValue()), result;

        if (left != NULL) {
            result = treeWalk(left) + " <-- ";
        }
        result += value;
        if (right != NULL) {
            result += " --> " + treeWalk(right);
        }
        return "(" + result + ")";
    }
};

class BTree {
    private:
        struct Tree* tree;

    public:
        BTree(int n) {
            tree = new Tree(5);
        }
        void addNode(int n) {
            tree -> addNode(n);
        }
        void removeNode(int n) {
            tree -> removeNode(n);
        }
        void printTree() {
            tree -> treeWalk();
        }
};

int main() {
    BTree tree(5);

    tree.addNode(3);
    tree.addNode(1);
    tree.addNode(2);
    tree.addNode(7);
    tree.addNode(6);

    tree.printTree();
    tree.removeNode(5);
    tree.removeNode(6);
    tree.printTree();

    return 0;
}