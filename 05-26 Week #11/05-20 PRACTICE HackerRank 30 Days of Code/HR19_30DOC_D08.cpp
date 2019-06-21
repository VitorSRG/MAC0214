/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 8: Dictionaries and Maps"
 -  link:       https://www.hackerrank.com/challenges/30-dictionaries-and-maps/problem
 -  hash:       HR19_30DOC_D08

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation map query online

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int main() {
    int n;
    cin >> n;

    map<string, string> friend_phone;

    for (int i = 0; i < n; i++) {
        string name, phone;
        cin >> name >> phone;
        friend_phone[name] = phone;
    }

    string q;
    while (cin >> q) {
        if (friend_phone.find(q) == friend_phone.end())
            cout << "Not found" << endl;
        else
            cout << q << '=' << friend_phone[q] << endl;
    }

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                3
                sam 99912222
                tom 11122222
                harry 12299933
                sam
                edward
                harry
    output:     |
                sam=99912222
                Not found
                harry=12299933
 ******************************************************************************/
