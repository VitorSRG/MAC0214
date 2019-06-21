/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 16: Exceptions - String to Integer"
 -  link:       https://www.hackerrank.com/challenges/30-exceptions-string-to-integer/problem
 -  hash:       HR19_30DOC_D16

 -  author:     Vitor SRG
 -  version:    1.0 29/03/2019

 -  tags:       implementation parse exception

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int main() {
    string s;
    cin >> s;
    
    int a;
    size_t l;
    try {
        a = stoi(s);
        
        cout << a << endl;
    } catch (invalid_argument) {
        cout << "Bad String" << endl;
    }
}


/******************************************************************************
 -  test:
    input:      |
                3
    output:     |
                3
 -  test:
    input:      |
                za
    output:     |
                Bad String
 ******************************************************************************/
