/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 6: Let's Review"
 -  link:       https://www.hackerrank.com/challenges/30-review-loop/problem
 -  hash:       HR19_30DOC_D06

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
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        string s;
        cin >> s;

        for (int i = 0; i < s.size(); i += 2)
            cout << s[i];
        cout << ' ';
        for (int i = 1; i < s.size(); i += 2)
            cout << s[i];
        cout << endl;
    }

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                2
                Hacker
                Rank
    output:     |
                Hce akr
                Rn ak
 ******************************************************************************/
