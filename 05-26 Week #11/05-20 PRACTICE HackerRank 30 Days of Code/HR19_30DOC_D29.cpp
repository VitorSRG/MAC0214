/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 29: Bitwise AND"
 -  link:       https://www.hackerrank.com/challenges/30-bitwise-and/problem
 -  hash:       HR19_30DOC_D29

 -  author:     Vitor SRG
 -  version:    1.0 05/04/2019

 -  tags:       bitwise and tests query online

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int main(int argc, char * argv[]) {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int n, k;
        cin >> n >> k;

        int a = k-1;
        int b = ~a & (a+1);

        if ((a | b) > n)
            cout << a-1 << endl;
        else
            cout << a << endl;
    }

    return EXIT_SUCCESS;
}


/******************************************************************************
 -  test:
    input:      |
                3
                5 2
                8 5
                2 2
    output:     |
                1
                4
                0
 -  test:
    input:      !file "{dirabs}/HR19_30DOC_D29.2.in"
    output:     !file "{dirabs}/HR19_30DOC_D29.2.out"
 -  test:
    input:      !file "{dirabs}/HR19_30DOC_D29.5.in"
    output:     !file "{dirabs}/HR19_30DOC_D29.5.out"
 ******************************************************************************/
