/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 15: Linked List"
 -  link:       https://www.hackerrank.com/challenges/30-linked-list/problem
 -  hash:       HR19_30DOC_D15

 -  author:     Vitor SRG
 -  version:    1.0 29/03/2019

 -  tags:       implementation class object linked_list

 -  language:   C++14
 ******************************************************************************/


#include <iostream>
#include <cstddef>

using namespace std;	

class Node {
public:
    int data;
    Node *next;
    Node(int d){
        data=d;
        next=NULL;
    }
};

class Solution{
public:
    Node* insert(Node *head, int data) {
        if (!head)
            return new Node(data);

        Node* node = head;

        while (node->next)
            node = node->next;

        node->next = new Node(data);

        return head;
    }

    void display(Node *head) {
        Node *start=head;
        while(start) {
            cout<<start->data<<" ";
            start=start->next;
        }
    }
};

int main() {
    Node* head=NULL;
    Solution mylist;
    int T,data;
    cin>>T;
    while(T-->0){
        cin>>data;
        head=mylist.insert(head,data);
    }   
    mylist.display(head);
}


/******************************************************************************
 -  test:
    input:      |
                4
                2
                3
                4
                1
    output:     |
                2 3 4 1
 ******************************************************************************/
