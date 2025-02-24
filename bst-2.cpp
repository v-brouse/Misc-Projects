#include "bst.h"

template <typename T>
void BST<T>::insert(T data) {

    // enter the tree at its root with the data
    this->root = traverseAdd(this->root, data);
}

template <typename T>
Node<T>* BST<T>::traverseAdd(Node<T>* node, T data) {

    // check if the root is null, and if so add a new node there and set its parent to
    // our current node
    if (node == nullptr) {
        auto* temp = new Node<T>(data);
        return temp;
    }

    // if the data we are inserting is less than of the node we are currently at,
    // traverse left. otherwise, traverseAdd right
    if (data < node->data) {
        node->left = traverseAdd(node->left, data);
        node->left->parent = node;
    } else if (data > node->data) {
        node->right = traverseAdd(node->right, data);
        node->right->parent = node;
    }

    // retrieve the height of the children nodes, determine which one is bigger, and
    // set the height of the current node to the greater height + 1
    node->height = 1 + std::max(height(node->left), height(node->right));

    // return the current node
    return node;
}

template <typename T>
int BST<T>::height(Node<T>* node) {

    if (node == nullptr) {
        return -1; // if the node is null, return -1.
    } else {
        return node->height; // otherwise, return its height
    }
}

/**
 * This function was written entirely by AI given the header file and the context.
 */
template <typename S>
std::ostream& operator<<(std::ostream& os, const BST<S>& tree) {
    print(os, tree.root);
    return os;
}

/**
 * This function was written entirely by AI given the header file and the context.
 */
template <typename S>
void print(std::ostream& os, Node<S>* node) {

    // if the node is not null, recursively print it
    if (node) {
        print(os, node->left);
        os << node->data << ' ';
        print(os, node->right);
    }
}

/**
 * This function was written entirely by AI given the header file and the context.
 */
template <typename T>
void BST<T>::remove(Node<T>* node) {

    // destructor logic
    if (node->left != 0)
        remove(node->left);
    if (node->right != 0)
        remove(node->right);

    delete node;
}