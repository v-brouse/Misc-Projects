#include <iostream>
#include <cmath>
#include "avl_tree.cpp"

using namespace std;

/**
 * Performs n inversions on a given array.
 *
 * @return a pointer to the inverted array.
 */
int* invert(int, const int*);

/**
 * Calculates the average height of a BST tree over 100 trials, given a number of
 * inversions n.
 */
int getAvgBST (int n, int, int*);

/**
 * Calculates the average height of an AVL tree over 100 trials, given a number of
 * inversions n.
 */
int getAvgAVL (int n, int, int*);

int main() {

    int size; // size of array
    int* arr; // array to build trees


    // perform from 2^10 to 2^20 insertions
    for (int i = 10; i <= 20; ++i) {

        size = pow(2, i); // get the size of the array
        arr = new int[size]; // initialize array

        // fill array with values from 0 to 2^i
        for (int j = 0; j < size; ++j) {
            arr[j] = j;
        }

        // get the averages for the 4 trials
        int bstAvg = getAvgBST(size, size, arr);
        int avlAvg = getAvgAVL(size, size, arr);
        int bst100nAvg = getAvgBST(100 * size, size, arr);
        int avl100nAvg = getAvgAVL(100 * size, size, arr);

        // print results of tests
        cout << "2^" << i << " keys: ";
        cout << bstAvg << " " << avlAvg << " " << bst100nAvg << " " << avl100nAvg << endl;
    }

    return 0;
}

int* invert(int n, const int* arr) {

    // create a pointer to a new int array
    int* newArr = new int[n];

    // copy the values from the provided one
    for (int i = 0; i < n; ++i) {
        newArr[i] = arr[i];
    }

    // make inversions up to n times
    for (int i = 0; i <= n; ++i) {

        // get a random index between 0 and n
        int index = rand() % n;

        // check if the following index is out of bounds, and if it's already inverted
        if (index + 1 < n && newArr[index] < newArr[index + 1]) {

            int temp = newArr[index]; // store the lesser value
            newArr[index] = newArr[index + 1]; // get the greater value
            newArr[index + 1] = temp; // assign lesser value
        } else {
            // if the index is no good or out of bounds, decrement the counter to try
            // again
            i--;
        }
    }

    return newArr;
}


int getAvgBST(int n, int size, int* arr) {

    // record the heights of every trial
    int heights = 0;

    // perform 100 trials
    for (int i = 0; i <= 100; ++i) {

        int* newArr = invert(n, arr); // initialize a new array
        BST<int>* tree = new BST<int>(); // initialize a new tree

        // insert all the keys into the tree
        for (int j = 0; j < size; j++) {
            tree->insert(newArr[j]);
        }

        // record its height
        heights += tree->height();
    }

    // return the average
    return static_cast<double>(heights) / 100.0;
}


int getAvgAVL(int n, int size, int* arr) {

    // record the heights of every trial
    int heights = 0;

    // perform 100 trials
    for (int i = 0; i <= 100; ++i) {

        int* newArr = invert(n, arr); // initialize a new array
        AvlTree<int>* tree = new AvlTree<int>(); // initialize a new tree

        // insert all the keys into the tree
        for (int j = 0; j < size; j++) {
            tree->insert(newArr[j]);
        }

        // record its height
        heights += tree->height();
    }

    // return the average
    return static_cast<double>(heights) / 100.0;
}

