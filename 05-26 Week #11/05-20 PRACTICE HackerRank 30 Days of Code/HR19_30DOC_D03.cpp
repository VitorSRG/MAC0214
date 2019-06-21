/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 3: Intro to Conditional Statements"
 -  link:       https://www.hackerrank.com/challenges/30-conditional-statements/problem
 -  hash:       HR19_30DOC_D03

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation cases

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int main() {
    int n;
    cin >> n;

    if (n % 2 == 1)             cout << "Weird";
    else if (n >= 2 && n <= 5)  cout << "Not Weird";
    else if (n >= 6 && n <= 20) cout << "Weird";
    else if (n > 20)            cout << "Not Weird";

    cout << endl;

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                3
    output:     |
                Weird

 -  test:
    input:      |
                24
    output:     |
                Not Weird
 ******************************************************************************/
