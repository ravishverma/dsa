#include <iostream>

namespace BinaryTree
{

struct Node {
    int value;
    Node* right;
    Node* left;
    Node* parent;
    Node(int val): value(val), right(nullptr), left(nullptr), parent(nullptr) {}

    friend std::ostream& operator<<(std::ostream& os, const Node* root) {
        if (root == nullptr) {
            return os;
        }

        os << root->left;
        os << root->value << " ";
        os << root->right;

        return os;
    }

};

Node* minimum(Node* root) {
    Node* minNode = nullptr;
    Node* x = root;
    while (x!=nullptr) {
        minNode = x;
        x = x->left;
    }

    return minNode;
}

Node* maximum(Node* root) {
    Node* maxNode = nullptr;
    Node* x = root;
    while (x!=nullptr) {
        maxNode = x;
        x = x->right;
    }

    return maxNode;
}

Node* searchNN(Node* root, int value) {
    // Look for parent
    Node* parent = nullptr;
    Node* x = root;
    while (x != nullptr) {
        parent = x;

        if (value <= x->value) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    return parent;
}

Node* successor(Node* root, int value) {
    Node* node = searchNN(root, value);

    if (node->right != nullptr) {
        return minimum(node->right);
    }

    Node* x = node;
    Node* parent = node->parent;
    while (parent != nullptr &&
            parent->right != nullptr &&
            x->value == parent->right->value) {
        x = parent;
        parent = parent->parent;
    }

    return parent;
}

Node* predecessor(Node* root, int value) {
    Node* node = searchNN(root, value);

    if (node->left != nullptr) {
        return maximum(node->left);
    }

    Node* x = node;
    Node* parent = node->parent;
    while (parent != nullptr &&
            parent->left !=nullptr &&
            x->value == parent->left->value) {
        x = parent;
        parent = parent->parent;
    }

    return parent;
}

void insert(Node* &root, int value) {
    Node* node = new Node(value);

    if (root == nullptr) {
        root = node;
        return;
    }

    // Look for parent
    Node* parent = searchNN(root, value);
    node->parent = parent;

    if (node->value <= parent->value) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

void transplant(Node* &root, Node* &target, Node* &source) {
    if (target==nullptr) {
        return;
    }

    if (target->parent == nullptr) {
        root = source;
    } else if (target->parent->left != nullptr &&
               target->value == target->parent->left->value) {
        target->parent->left = source;
    } else if (target->parent->right != nullptr &&
                target->value == target->parent->right->value) {
        target->parent->right = source;
    }

    if (source != nullptr) {
        source->parent = target->parent;
    }
}

void eliminate(Node* &root, int value) {
    // Look for node
    Node* node = searchNN(root, value);
    
    if (node->left == nullptr) {
        transplant(root, node, node->right);
    } else if (node->right == nullptr) {
        transplant(root, node, node->left);
    } else {
        Node* y = minimum(node->right);

        if (y->value != node->right->value) {
            transplant(root, y, y->right);
            y->right = node->right;
            node->right->parent = y;
        }

        transplant(root, node, y);
        y->left = node->left;
        y->left->parent = y;
    }
}
}
