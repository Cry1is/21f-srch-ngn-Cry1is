//
// Created by Zachary on 11/17/2021.
//

#include "catch.hpp"

#include "AVLTree.h"

TEST_CASE("AVLTree", "[AVLTree]") {
    AVLTree<int, int>* tree = new AVLTree<int, int>();
    int nums[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    for (int i = 0; i < 15; i++)
        cout << tree->insert(nums[i], nums[14-i]) << " ";
    cout << endl;
    cout << *tree << endl;
}