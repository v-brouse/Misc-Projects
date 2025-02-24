#include "avl_tree.h"
using namespace std;

template <typename T>
Node<T> *AvlTree<T>::insert(T data) {
    Node<T> *newNode = BST<T>::insert(data); // Perform BST insertion
    // Get another reference to newNode to iterate up the tree when checking for imbalances, since we need the reference
    // above in order to return it at the end of the function.
    Node<T> *balanceChecker = newNode;

    // The logic here is incorrect. The loop doesn't ever execute because the loop condition this->unbalanced(newNode)
    // will never be true after inserting a new node (with height 0) into the tree.
    // Once you do find an unbalanced node, you also need to pick the correct nodes to restructure. The correct nodes to
    // pick to restructure are the lowest unbalanced node (the node we stop the loop at), the highest child of that
    // node, and the highest child of *that* node. In other words, you have to walk back down the tree two nodes, rather
    // than continuing up it. This was the mistake I brought up in the email I sent earlier this week, if you need a
    // visual.
    // Your logic for checking which rotation to perform should be something like (example for left-left):
    // if (balanceChecker->data > middleNode->data && middleNode->data > bottomNode->data) {
    //    balanceChecker = this->rotateLeft(balanceChecker);
    // }
//  // Check for and fix imbalances
//    while (newNode != nullptr && this->unbalanced(newNode)) {
//        Node<T>* parent = newNode->parent;
//        if (parent != nullptr) {
//            Node<T>* grandparent = parent->parent;
//            if (grandparent != nullptr) {
//                if (newNode->data < parent->data && parent->data < grandparent->data) {
//                    // Left-Left case
//                    newNode = this->rotateRight(grandparent);
//                } else if (newNode->data > parent->data && parent->data > grandparent->data) {
//                    // Right-Right case
//                    newNode = this->rotateLeft(grandparent);
//                } else if (newNode->data > parent->data && parent->data < grandparent->data) {
//                    // Left-Right case
//                    this->rotateLeft(parent);
//                    newNode = this->rotateRight(grandparent);
//                } else if (newNode->data < parent->data && parent->data > grandparent->data) {
//                    // Right-Left case
//                    this->rotateRight(parent);
//                    newNode = this->rotateLeft(grandparent);
//                }
//            }
//        }
//
//        this->updateHeights(newNode);
//        newNode = newNode->parent; // Move up the tree
//    }

    // The goal should be to walk up the tree as long as the current node isn't a null pointer (meaning we've walked up
    // the tree all the way past the root without finding an unbalanced node) or until we find an unbalanced node (when
    // unbalanced is true)
    while (balanceChecker != nullptr && !this->unbalanced(balanceChecker)) {
        balanceChecker = balanceChecker->parent;
    }
    // at this point, either newNode is null--meaning we've made it to the top of the tree without needing to
    // re-balance--or the tree is unbalanced, and we need to re-balance.
    if (balanceChecker != nullptr) {
        Node<T> *firstChild = trinode_successor(balanceChecker, newNode->data);
        Node<T> *secondChild = trinode_successor(firstChild, newNode->data);
        // Include some logic here to make sure you're correctly re-assigning the child node of the parent of the
        // highest node in the restructuring--balanceChecker.
        // To give an example to explain this issue: imagine the highest node you're restructuring is the left child of
        // its parent node. After the restructuring is performed, the highest node in the restructuring will no longer
        // be the highest node--it got pushed farther down the tree--but for all that its former parent knows, it's
        // still its child. You'd need to re-assign the left child of that parent node to the new highest node after the
        // restructuring.
        // I would consider it more natural to take the trinode_restructure node arguments in height order (decreasing),
        // but I've listed them here to agree with your logic for selecting the rotations in trinode_restructure().
        // Personal preference.
        balanceChecker = trinode_restructure(firstChild, balanceChecker, secondChild);
    }
    while (balanceChecker != nullptr) {
        // After you trinode restructure, you'll also need to adjust the heights of the nodes above it, since a trinode
        // restructuring always results in the height of the tree being reduced, so make sure to include this logic as
        // you walk the remaining height of the tree back up.
        balanceChecker = balanceChecker->parent;
    }

    return newNode;
}
template <typename T>
Node<T> *AvlTree<T>::trinode_successor(Node<T> *x, T data)
{
    // This logic appears to return the first Node in the tree whose data value is larger than the specified data value,
    // or the lowest Node in the tree whose data value is the same as the specified data value (when you call the
    // function by specifying the root node).
    // This isn't what this function is supposed to do; this function is supposed to accept a node and determine which
    // of its children has the greater height, since the nodes picked when selecting the nodes for trinode restructuring
    // are always the child nodes of some node with the greatest height.
//    while (x != nullptr)
//    {
//        if (data < x->data)
//        {
//            if (x->left == nullptr || data >= x->left->data)
//            {
//                return x;
//            }
//            x = x->left;
//        }
//        else
//        {
//            x = x->right;
//        }
//    }
//    return nullptr;

    // Since Dr. Coles pasted his AVL trinode_successor function on Brightspace, I've copied it here. Like he says in
    // his post, though, the T data parameter of this function isn't really useful, since it's only checked if a and b
    // aren't the same height, which can never be the case when trinode restructuring.
    int a = BST<T>::height(x->left);
    int b = BST<T>::height(x->right);
    if (a > b || (a == b && data <= x->data)) {
        return x->left;
    }
    else return x->right;
}

template <typename T>
Node<T> *AvlTree<T>::trinode_restructure(Node<T> *x, Node<T> *y, Node<T> *z)
{
    // I believe this logic here for selecting which rotation to perform holds if you consider x to be the middle node,
    // y to be the lowest node, and z to be the highest node.
    // However, the nodes that you pass to these functions aren't correct if my above comment holds. For example, on
    // line 353, rotateRight() takes y--the lowest node in the restructuring--as an argument, and rotateRight() then
    // considers its children, which cannot be in the restructuring since y was just established to be the lowest node
    // of the restructuring.
    cout << "------------" << endl;
    if ((y->data < x->data && x->data < z->data) || (z->data < x->data && x->data < y->data)) {
        // Single rotation (Right-Left or Left-Right)
        if (y->data < x->data && x->data < z->data) {
            return this->rotateRight(y);
        } else {
            return this->rotateLeft(y);
        }
    } else {
        // Double rotation (Left-Left or Right-Right)
        if (y->data < x->data && z->data < x->data) {
            this->rotateRight(x);
            return this->rotateLeft(z);
        } else {
            this->rotateLeft(x);
            return this->rotateRight(z);
        }
    }
}

// rotateLeft() and rotateRight() will not end up with a correctly-rotated AVL subtree, since they don't consider the
// relations of nodes a, b, c, and d in Dr. Coles's ASCII drawings (and for the reasons specified in my comment in
// trinode_restructure()
template <typename T>
Node<T> *AvlTree<T>::rotateLeft(Node<T> *x)
{
    Node<T> *y = x->right;
    Node<T> *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(this->height(x->left), this->height(x->right)) + 1;
    y->height = max(this->height(y->left), this->height(y->right)) + 1;
    return y;
}

template <typename T>
Node<T> *AvlTree<T>::rotateRight(Node<T> *y)
{
    Node<T> *x = y->left;
    Node<T> *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(this->height(y->left), this->height(y->right)) + 1;
    x->height = max(this->height(x->left), this->height(x->right)) + 1;
    return x;
}

template <typename T>
bool AvlTree<T>::unbalanced(Node<T> *node)
{
    // This function looks good!
    if (node == nullptr) {
        return false; // Null node cannot be unbalanced
    }

    int balance = this->height(node->left) - this->height(node->right);
    if (balance > 1 || balance < -1) {
        return true;
    }

    return false;
}

template <typename T>
int AvlTree<T>::updateHeights(Node<T> *node)
{
    // Dr. Coles specified that we shouldn't update the heights of the entire tree recursively after an insertion.
    // There's a way to do it only as necessary as you walk back up the tree after an AVL rotation has been performed--
    // I hint to this in my comment in your insert method.
    if (node == nullptr)
    {
        return -1; // Height of null node is -1
    }

    int leftHeight = updateHeights(node->left);
    int rightHeight = updateHeights(node->right);

    node->height = max(leftHeight, rightHeight) + 1;

    // cout << "Updated height of node with data " << node->data << " to " << node->height << endl;

    return node->height;
}

// int height(Node<T> *node) should already be defined in BST, so you don't need to shadow it here.
template <typename T>
int AvlTree<T>::height(Node<T> *node)
{
    // int height(Node<T> *node) should already be defined in BST, so you don't need to shadow it here.
    // Also, this will return that a null node has height 0, when it should be -1.
    int h = 0;
    if (node != NULL)
    {
        int l_height = this->height(node->left); // you should be able to use node->height here rather than
        int r_height = this->height(node->right); // relying on recursion to re-calculate it each time
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

// I'm not sure what this is doing here, but I'm curious
template class AvlTree<int>;