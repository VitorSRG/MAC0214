/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 10: Binary Numbers"
 -  link:       https://www.hackerrank.com/challenges/30-binary-numbers/problem
 -  hash:       HR19_30DOC_D10

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation binary loop

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int main() {
    int n;
    cin >> n;

    int maxseq1 = 0;
    int lenseq1 = 0;
    int last = 0;

    do {
        if (n%2) {
            lenseq1++;
            maxseq1 = max(maxseq1, lenseq1);
        }
        else {
            lenseq1 = 0;
        }
    } while (n = n/2);

    cout << maxseq1 << endl;

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                5
    output:     |
                1
 -  test:
    input:      |
                13
    output:     |
                2
 ******************************************************************************/
