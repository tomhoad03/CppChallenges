#include <iostream>
#include <vector>

using namespace std;

// node structure
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

    // adds a node to the whole tree
    void addNode(int v) {
        addNode(root, v);
    }

    // adds a node to a subtree
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

    // removes a node from the whole tree
    void removeNode(int v) {
        removeNode(root, NULL, v);
    }

    // removes a node from a subtree
    void removeNode(struct Node* node, struct Node* parentNode, int v1) {
        struct Node* left = node -> getLeftChild();
        struct Node* right = node -> getRightChild();
        int v2 = node -> getValue();

        if (v1 == v2) {

            // replaces the node with the largest value on its left subtree
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

            // replaces the node with the largest value on its right subtree    
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

            // removes a node that has no children
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

    // walks across the whole tree
    void treeWalk() {
        string values = treeWalk(root);
        cout << values << endl;
    }

    // walks across a subtree
    string treeWalk(struct Node* node) {
        struct Node* left = node -> getLeftChild();
        struct Node* right = node -> getRightChild();

        string value = to_string(node -> getValue()), result;

        if (left != NULL) {
            result = treeWalk(left) + " <-- ";
        }
        result += value;
        if (right != NULL) {
            result += " --> " + treeWalk(right);
        }
        return "(" + result + ")";
    }

    // gets the height of the whole tree
    void treeHeight() {
        int height = treeHeight(root, 1);
        cout << "Tree height: " << height << endl;
    }

    // gets the height of a subtree
    int treeHeight(struct Node* node, int currentHeight) {
        struct Node* left = node -> getLeftChild();
        struct Node* right = node -> getRightChild();

        int leftHeight = 0, rightHeight = 0;

        if (left != NULL) {
            leftHeight = treeHeight(left, currentHeight + 1);
        }
        if (right != NULL) {
            rightHeight = treeHeight(right, currentHeight + 1);
        }
        if (leftHeight >= rightHeight && leftHeight >= currentHeight) {
            return leftHeight;
        } else if (rightHeight > leftHeight && rightHeight >= currentHeight) {
            return rightHeight;
        } else {
            return currentHeight;
        }
    }
};

// binary tree class for abstraction
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
        void printHeight() {
            tree -> treeHeight();
        }
};

/*
Possible tasks:
1. Is a tree complete?
2. User inputs
3. Improved pretty print
4. Nodes with multiple children
5. More general BST functions
*/

// main
int main() {
    BTree tree(5);

    tree.addNode(3);
    tree.addNode(1);
    tree.addNode(2);
    tree.addNode(7);
    tree.addNode(6);

    tree.printTree();
    tree.printHeight();

    tree.removeNode(5);
    tree.removeNode(6);

    tree.printTree();
    tree.printHeight();

    return 0;
}