/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 11: 2D Arrays"
 -  link:       https://www.hackerrank.com/challenges/30-2d-arrays/problem
 -  hash:       HR19_30DOC_D11

 -  author:     Vitor SRG
 -  version:    1.0 29/03/2019

 -  tags:       implementation array

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


template<size_t N, size_t M>
int convolve_hourglass(const int (&arr)[N][M], int i, int j) {
    return + arr[i+0][j+0] + arr[i+0][j+1] + arr[i+0][j+2]
                           + arr[i+1][j+1]
           + arr[i+2][j+0] + arr[i+2][j+1] + arr[i+2][j+2];
}


int main() {
    int n = 6;
    int arr[6][6];

    int maxsum = INT_MIN;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];

    for (int i = 0; i <= n-3; i++)
        for (int j = 0; j <= n-3; j++)
            maxsum = max(maxsum, convolve_hourglass(arr, i, j));

    cout << maxsum << endl;

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                1 1 1 0 0 0
                0 1 0 0 0 0
                1 1 1 0 0 0
                0 0 2 4 4 0
                0 0 0 2 0 0
                0 0 1 2 4 0
    output:     |
                19
 ******************************************************************************/
