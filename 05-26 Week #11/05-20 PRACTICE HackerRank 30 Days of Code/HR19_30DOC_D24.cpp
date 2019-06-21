/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 24: More Linked Lists"
 -  link:       https://www.hackerrank.com/challenges/30-linked-list-deletion/problem
 -  hash:       HR19_30DOC_D24

 -  author:     Vitor SRG
 -  version:    1.0 05/04/2019

 -  tags:       linked_list recursion

 -  language:   C++14
 ******************************************************************************/


#include <cstddef>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;


class Node {
public:
    int data;
    Node *next;

    Node(int d) {
        data=d;
        next=NULL;
    }
};

class Solution {
public:
    Node* removeDuplicates(Node* head) {
        if (!head)
            return head;

        head->next = removeDuplicates(head->next, head->data);
        head->next = removeDuplicates(head->next);
        return head;
    }

    Node* removeDuplicates(Node* head, int data) {
        if (!head)
            return head;
        if (head->data == data)
            return removeDuplicates(head->next, data);
        
        head->next = removeDuplicates(head->next, data);
        return head;
    }

    Node* insert(Node *head,int data) {
        Node* p=new Node(data);

        if (head==NULL) {
            head=p;  
        }
        else if (head->next==NULL) {
            head->next=p;

        }
        else {
            Node *start=head;
            while (start->next!=NULL) {
                start=start->next;
            }
            start->next=p;   

        }
        return head;
    }

    void display(Node *head) {
        Node *start=head;
        while (start) {
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
    while (T-->0){ 
        cin>>data;
        head=mylist.insert(head,data);
    }	
    head=mylist.removeDuplicates(head);

    mylist.display(head);
}


/******************************************************************************
 -  test:
    input:  |
            6
            1
            2
            2
            3
            3
            4
    output: |-
            1 2 3 4
 ******************************************************************************/
