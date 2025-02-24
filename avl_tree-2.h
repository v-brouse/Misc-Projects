/*
 * An AVL tree. Deletions are not supported.
 *
 * Author: Drue Coles
 */

#include "bst.cpp"

template <typename T>
class AvlTree : public BST<T> {

public:
    void insert(T data);

private:

    void trinode_restructure(Node<T>*, Node<T>*, Node<T>*);
    void checkTree(Node<T>*, T);
    void checkBalance(Node<T>*);
    int updateHeight(Node<T>* node);
    void trinode_LL(Node<T>* x, Node<T>* y, Node<T>* z);
    void trinode_RL(Node<T>* x, Node<T>* y, Node<T>* z);
    void trinode_RR(Node<T>* x, Node<T>* y, Node<T>* z);
    void trinode_LR(Node<T>* x, Node<T>* y, Node<T>* z);
};