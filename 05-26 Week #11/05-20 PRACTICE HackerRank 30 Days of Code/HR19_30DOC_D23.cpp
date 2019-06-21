/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 23: BST Level-Order Traversal"
 -  link:       https://www.hackerrank.com/challenges/30-binary-trees/problem
 -  hash:       HR19_30DOC_D23

 -  author:     Vitor SRG
 -  version:    1.0 05/04/2019

 -  tags:       binary_tree breadth_first_search

 -  language:   C++14
 ******************************************************************************/


#include <iostream>
#include <cstddef>
#include <queue>
#include <string>
#include <cstdlib>


using namespace std;


class Node {
public:
    int data;
    Node *left,*right;
    
    Node(int d) {
        data=d;
        left=right=NULL;
    }
};

class Solution {
public:
    Node* insert(Node* root, int data){
        if (root==NULL) {
            return new Node(data);
        }
        else {
            Node* cur;
            if (data<=root->data) {
                cur=insert(root->left,data);
                root->left=cur;
            }
            else {
                cur=insert(root->right,data);
                root->right=cur;
            }           
            return root;
        }
    }

    void levelOrder(Node* root){
        queue<Node*> queue;
        queue.push(root);

        while (!queue.empty()) {
            Node* node = queue.front();
            queue.pop();

            if (node) {
                cout << node->data << ' ';
                queue.push(node->left);
                queue.push(node->right);
            }
        }
    }
};

int main(){
    Solution myTree;
    Node* root=NULL;
    int T,data;
    cin>>T;
    while (T-->0) {
        cin>>data;
        root= myTree.insert(root,data);
    }
    myTree.levelOrder(root);
    return 0;
}


/******************************************************************************
 -  test:
    input:  |
            6
            3
            5
            4
            7
            2
            1
    output: |-
            3 2 5 1 4 7 
 ******************************************************************************/
