/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 20: Sorting"
 -  link:       https://www.hackerrank.com/challenges/30-sorting/problem
 -  hash:       HR19_30DOC_D20

 -  author:     Vitor SRG
 -  version:    1.0 29/03/2019

 -  tags:       implementation bubblesort invertion

 -  language:   C++14
 ******************************************************************************/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;


int main() {
    int n;
    cin >> n;

    vector<int> a(n, 0);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int numberOfSwaps = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                numberOfSwaps++;
            }
        }
    }
    
    cout << "Array is sorted in " << numberOfSwaps << " swaps." << endl;
    cout << "First Element: " << a[0] << endl;
    cout << "Last Element: " << a[a.size()-1] << endl;

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                3
                1 2 3
    output:     |
                Array is sorted in 0 swaps.
                First Element: 1
                Last Element: 3
 -  test:
    input:      |
                3
                3 2 1
    output:     |
                Array is sorted in 3 swaps.
                First Element: 1
                Last Element: 3
 ******************************************************************************/
