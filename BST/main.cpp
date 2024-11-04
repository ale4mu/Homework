#include <iostream>
#include "BinarySearchTree.h"  // 假设 BinarySearchTree 类定义在这个头文件中

void testBinarySearchTree() {
    BinarySearchTree<int> bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);
    bst.insert(2);
    bst.insert(4);
    std::cout << "Initial Tree:" << std::endl;
    bst.printTree();

    // 测试remove函数

    //待删除的节点不存在的情况
    bst.remove(33);
    std::cout << "Tree after removing 33:" << std::endl;
    bst.printTree();


    //无子节点的情况
    bst.remove(7);
    std::cout << "Tree after removing 7:" << std::endl;
    bst.printTree();

    //有两个子节点的情况
    bst.remove(3);
    std::cout << "Tree after removing 3:" << std::endl;
    bst.printTree();

    //有一个子节点的情况
    bst.remove(2);
    std::cout << "Tree after removing 2:" << std::endl;
    bst.printTree();

    //删除root的情况
    bst.remove(10);
    std::cout << "Tree after removing 10:" << std::endl;
    bst.printTree();


    //测试树只有一个root节点且将被删除的情况
    BinarySearchTree<int> bst1;
    bst1.insert(5);
    std::cout << " tree bst1:" << std::endl;
    bst1.printTree();
    bst1.remove(5);
    std::cout << "bst1 after removing 5:" << std::endl;
    bst1.printTree();

    //测试在空树中试图删除元素的情况
    bst1.remove(0);
    std::cout << "bst1 after removing 0:" << std::endl;
    bst1.printTree();
}

int main() {
    testBinarySearchTree();
    return 0;
}