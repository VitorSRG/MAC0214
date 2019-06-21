/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 25: Running Time and Complexity"
 -  link:       https://www.hackerrank.com/challenges/30-running-time-and-complexity/problem
 -  hash:       HR19_30DOC_D25

 -  author:     Vitor SRG
 -  version:    1.0 05/04/2019

 -  tags:       primes query online

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int main() {
    int t;
    cin >> t;

    for (int ti = 1; ti <= t; ti++) {
        int q;
        cin >> q;

        if (q == 1)
            goto not_prime;

        for (int i = 2; i*i <= q; i++)
            if (q%i == 0)
                goto not_prime;

        cout << "Prime" << endl;

        continue;
        not_prime:
            cout << "Not prime" << endl;
    }
    
    return 0;
}


/******************************************************************************
 -  test:
    input:  |
            3
            12
            5
            7
    output: |
            Not prime
            Prime
            Prime
 ******************************************************************************/
