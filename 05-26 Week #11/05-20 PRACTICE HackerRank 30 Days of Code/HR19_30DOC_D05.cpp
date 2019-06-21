/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 5: Loops"
 -  link:       https://www.hackerrank.com/challenges/30-loops/problem
 -  hash:       HR19_30DOC_D05

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation loop

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= 10; i++)
        cout << n << " x " << i << " = " << i*n << endl;

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                2
    output:     |
                2 x 1 = 2
                2 x 2 = 4
                2 x 3 = 6
                2 x 4 = 8
                2 x 5 = 10
                2 x 6 = 12
                2 x 7 = 14
                2 x 8 = 16
                2 x 9 = 18
                2 x 10 = 20
 ******************************************************************************/
