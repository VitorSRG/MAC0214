/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 9: Recursion 3"
 -  link:       https://www.hackerrank.com/challenges/30-recursion/problem
 -  hash:       HR19_30DOC_D09

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation factorial

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int factorial(int n) {
    if (n <= 1)
        return 1;
    return n*factorial(n-1);
}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int result = factorial(n);

    fout << result << "\n";

    fout.close();

    return 0;
}


/******************************************************************************

 ******************************************************************************/
