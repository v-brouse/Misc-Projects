#include <iostream>
#include "avl_tree.h"

/**
 * Inserts a new node into the tree.
 */
template <typename T>
void AvlTree<T>::insert(T data) {

    // use inherited insert function
    BST<T>::insert(data);

    // search for newly inserting node and backtrack, comparing heights and
    // restructuring where needed
    checkTree(BST<T>::root, data);
}

/**
 * Searches tree for newly inserted data and calls check balance on its way recursing
 * back to check the if the tree is still balanced after inserting the new node.
 */
template <typename T>
void AvlTree<T>::checkTree(Node<T>* current, T data) {

    // if the node is found, return to its parent
    if (current->data == data) {
        return;

    } else if (data < current->data) {
        checkTree(current->left, data); // check left child

    } else if (data > current->data) {
        checkTree(current->right, data); // check right child
    }

    // after finding the inserted node, check if the tree is still balanced
    checkBalance(current);
}

/**
 * Checks the balance of the tree and calls on a restructure if needed.
 */
template <typename T>
void AvlTree<T>::checkBalance(Node<T>* node) {

    // if the node doesn't exist, return false
    if (node == nullptr) {
        return;
    }

    int leftHeight = BST<T>::height(node->left); // height of left node
    int rightHeight = BST<T>::height(node->right); // height of right node
    int difference = abs(leftHeight - rightHeight); // difference of the two heights

    // if the balance is not greater than 1, than nodes are not unbalanced
    if (difference <= 1) {
        return;
    }

    // pointer for nodes to be restructured
    Node<T> *y = nullptr;
    Node<T> *z = nullptr;

    // determine which nodes need to be restructured by comparing heights
    if (leftHeight > rightHeight) y = node->left;
    else y = node->right;
    if (BST<T>::height(y->left) > BST<T>::height(y->right)) z = y->left;
    else z = y->right;

    // call on function to perform restructure
    trinode_restructure(node, y, z);
}

/**
 * This function was initially written by AI, but later edited by hand to fit the
 * program's logic.
 */
template <typename T>
int AvlTree<T>::updateHeight(Node<T>* node) {

    if (node == nullptr) {
        return -1;  // if the node points to a null, return -1
    } else {
        int leftHeight = updateHeight(node->left); // recurse left down the tree
        int rightHeight = updateHeight(node->right); // recurse right down the tree
        node->height = 1 + std::max(leftHeight, rightHeight); // update the heights
        return node->height; // return the current node's height
    }
}

/**
 * This function was initially written by AI, but later edited by hand to fit the
 * program's logic.
 */
template <typename T>
void AvlTree<T>::trinode_restructure(Node<T>* x, Node<T>* y, Node<T>* z) {

    // determine the configuration of the trinode and perform restructuring
    if (x->left == y && y->left == z) {
        // Left-Left case
        trinode_LL(x, y, z);
        return;
    } else if (x->left == y && y->right == z) {
        // Left-Right case
        trinode_LR(x, y, z);
        return;
    } else if (x->right == y && y->left == z) {
        // Right-Left case
        trinode_RL(x, y, z);
        return;
    } else {
        // Right-Right case
        trinode_RR(x, y, z);
        return;
    }
}

/**
 * Performs a trinode restructure on a left-left case imbalance.
 */
template <typename T>
void AvlTree<T>::trinode_LL(Node<T>* x, Node<T>* y, Node<T>* z) {

    // set y's right child to x's left
    if (y->right == nullptr) {
        y->right = x;
        x->left = nullptr;
    } else {
        x->left = y->right;
        y->right = x;
    }

    // if x was the root node, have the root point to y. otherwise, rearrange parents
    if (x == BST<T>::root) {
        BST<T>::root = y;
    } else {

        // set y's parent to x's parent
        Node<T>* parent = x->parent;
        y->parent = parent;

        // set x's left or right child to y
        if (parent->right == x) {
            parent->right = y;
        } else {
            parent->left = y;
        }
    }

    // assign y as x's parent
    x->parent = y;

    // update the heights in the tree
    updateHeight(BST<T>::root);
}

/**
 * Performs a trinode restructure on a left-right case imbalance.
 */
template <typename T>
void AvlTree<T>::trinode_LR(Node<T>* x, Node<T>* y, Node<T>* z) {

    // set y's right child equal to z's left child
    if (z->left == nullptr) y->right = nullptr;
    else y->right = z->left;

    // set x's child equal to z's right child
    if (z->right == nullptr) x->left = nullptr;
    else x->left = z->right;

    z->left = y; // z's left child becomes y
    z->right = x; // z's right child becomes x

    // if x was the root node, have the root point to z. otherwise, rearrange parents
    if (x == BST<T>::root) {
        BST<T>::root = z;
    } else {

        // set z's parent to x's parent
        Node<T>* parent = x->parent;
        z->parent = parent;

        // set x's left or right child to z
        if (parent->right == x) {
            parent->right = z;
        } else {
            parent->left = z;
        }
    }

    // set z as x and y's parent
    y->parent = z;
    x->parent = z;

    // update the heights in the tree
    updateHeight(BST<T>::root);
}

/**
 * Performs a trinode restructure on a right-right case imbalance.
 */
template <typename T>
void AvlTree<T>::trinode_RR(Node<T>* x, Node<T>* y, Node<T>* z) {

    // set x's right child equal to y's left child
    if (y->left == nullptr) x->right = nullptr;
    else x->right = y->left;

    // set y's left child to x
    y->left = x;

    // if x was the root node, have the root point to y. otherwise, rearrange parents
    if (x == BST<T>::root) {
        BST<T>::root = y;
    } else {

        // set y's parent to x's parent
        Node<T>* parent = x->parent;
        y->parent = parent;

        // set x's left or right child to y
        if (parent->right == x) {
            parent->right = y;
        } else {
            parent->left = y;
        }
    }

    // set y as x's parent
    x->parent = y;

    // update the heights in the tree
    updateHeight(BST<T>::root);
}

/**
 * Performs a trinode restructure on a right-left case imbalance.
 */
template <typename T>
void AvlTree<T>::trinode_RL(Node<T>* x, Node<T>* y, Node<T>* z) {

    // set x's right child equal to z's left child
    if (z->left == nullptr) x->right = nullptr;
    else x->right = z->left;

    // set y's left child equal to z's right child
    if (z->right == nullptr) y->left = nullptr;
    else y->left = z->right;

    // assign z's children
    z->left = x;
    z->right = y;

    // if x was the root node, have the root point to z. otherwise, rearrange parents
    if (x == BST<T>::root) {
        BST<T>::root = z;
    } else {

        // set z's parent to x's parent
        Node<T>* parent = x->parent;
        z->parent = parent;

        // set x's left or right child to z
        if (parent->right == x) {
            parent->right = z;
        } else {
            parent->left = z;
        }
    }

    // set z as x and y's parent
    y->parent = z;
    x->parent = z;

    // update the heights in the tree
    updateHeight(BST<T>::root);
}