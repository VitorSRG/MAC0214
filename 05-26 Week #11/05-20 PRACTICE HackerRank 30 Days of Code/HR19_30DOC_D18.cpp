/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 18: Queues and Stacks"
 -  link:       https://www.hackerrank.com/challenges/30-queues-stacks/problem
 -  hash:       HR19_30DOC_D18

 -  author:     Vitor SRG
 -  version:    1.0 29/03/2019

 -  tags:       implementation class object queue stack palindrome

 -  language:   C++14
 ******************************************************************************/

#pragma GCC optimize ("O3", "Ofast", \
                      "unroll-loops", "rename-registers", \
                      "openmp")

#include <bits/stdc++.h>


using namespace std;


class Solution { 
public:
    queue<char> q;
    stack<char> s;

    void enqueueCharacter(char c) {
        q.push(c);
    }

    char dequeueCharacter() {
        char c = q.front();
        q.pop();
        return c;
    }

    void pushCharacter(char c) {
        s.push(c);
    }

    char popCharacter() {
        char c = s.top();
        s.pop();
        return c;
    }
};


int main() {
    // read the string s.
    string s;
    getline(cin, s);
    
    // create the Solution class object p.
    Solution obj;
    
    // push/enqueue all the characters of string s to stack.
    for (int i = 0; i < s.length(); i++) {
        obj.pushCharacter(s[i]);
        obj.enqueueCharacter(s[i]);
    }
    
    bool isPalindrome = true;
    
    // pop the top character from stack.
    // dequeue the first character from queue.
    // compare both the characters.
    for (int i = 0; i < s.length() / 2; i++) {
        if (obj.popCharacter() != obj.dequeueCharacter()) {
            isPalindrome = false;
            
            break;
        }
    }
    
    // finally print whether string s is palindrome or not.
    if (isPalindrome) {
        cout << "The word, " << s << ", is a palindrome.";
    } else {
        cout << "The word, " << s << ", is not a palindrome.";
    }
    
    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                racecar
    output:     |-
                The word, racecar, is a palindrome.
 ******************************************************************************/
