#include "binary_tree.h"

int main() {
    std::cout << "Test Binary Tree" << std::endl;

    BinaryTree::Node* bt = nullptr;

    int arr[] = {3, 4, 2, 6, 8, 1, 9};

    for (int i=0; i<sizeof(arr)/sizeof(int); i++) {
        BinaryTree::insert(bt, arr[i]);
    }

    std::cout << "Tree : " << bt << std::endl;
    std::cout << "Min : " << BinaryTree::minimum(bt) << std::endl;
    std::cout << "Max : " << BinaryTree::maximum(bt) << std::endl;

    std::cout << "NN 6 : " << BinaryTree::searchNN(bt,6) << std::endl;
    std::cout << "NN 7 : " << BinaryTree::searchNN(bt,7) << std::endl;

    std::cout << "Successor 6 : " << BinaryTree::successor(bt,6) << std::endl;
    std::cout << "Predecessor 6 : " << BinaryTree::predecessor(bt,6) << std::endl;

    BinaryTree::eliminate(bt, 6);
    std::cout << "Delete 6 : " << bt << std::endl;

    return 0;
}
