/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 7: Arrays"
 -  link:       https://www.hackerrank.com/challenges/30-arrays/problem
 -  hash:       HR19_30DOC_D07

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation array offline

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int main() {
    int n;
    cin >> n;

    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    for (int i = n-1; i > 0; i--)
        cout << arr[i] << ' ';
    cout << arr[0] << endl;

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                4
                1 4 3 2
    output:     |
                2 3 4 1
 ******************************************************************************/
