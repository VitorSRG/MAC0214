/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 0: Hello, World."
 -  link:       https://www.hackerrank.com/challenges/30-hello-world/problem
 -  hash:       HR19_30DOC_D00

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation string

 -  language:   C++14
 ******************************************************************************/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;


int main() {
    string inputString;
    getline(cin, inputString);
  
    cout << "Hello, World." << endl;
    cout << inputString << endl;

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                Welcome to 30 Days of Code!
    output:     |
                Hello, World.
                Welcome to 30 Days of Code!
 ******************************************************************************/
