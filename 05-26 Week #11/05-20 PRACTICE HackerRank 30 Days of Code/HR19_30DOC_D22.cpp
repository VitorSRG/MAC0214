/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 22: Binary Search Trees"
 -  link:       https://www.hackerrank.com/challenges/30-binary-search-trees/problem
 -  hash:       HR19_30DOC_D22

 -  author:     Vitor SRG
 -  version:    1.0 05/04/2019

 -  tags:       binary_tree recursion

 -  language:   C++14
 ******************************************************************************/


#include <iostream>
#include <cstddef>


using namespace std;	


class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    Node* insert(Node* root, int data) {
        if (root == NULL) {
            return new Node(data);
        }
        else {
            Node* cur;
            if (data <= root->data) {
                cur = insert(root->left, data);
                root->left = cur;
            }
            else {
                cur = insert(root->right, data);
                root->right = cur;
            }

            return root;
        }
    }

    int getHeight(Node* root) {
        if (!root)
            return 0;
        if (!root->left && !root->right)
            return 0;
        return 1 + max(getHeight(root->left), 
                       getHeight(root->right));
    }

};

int main() {
    Solution myTree;
    Node* root = NULL;
    int t;
    int data;

    cin >> t;

    while (t-- > 0) {
        cin >> data;
        root = myTree.insert(root, data);
    }
    int height = myTree.getHeight(root);
    cout << height;

    return 0;
}
 


/******************************************************************************
 -  test:
    input:  |
            7
            3
            5
            2
            1
            4
            6
            7
    output: |-
            3
 ******************************************************************************/
