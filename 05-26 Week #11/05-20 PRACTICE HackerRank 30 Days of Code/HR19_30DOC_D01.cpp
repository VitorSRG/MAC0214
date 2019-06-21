/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 1: Data Types"
 -  link:       https://www.hackerrank.com/challenges/30-data-types/problem
 -  hash:       HR19_30DOC_D01

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation string

 -  language:   C++14
 ******************************************************************************/


#include <iostream>
#include <iomanip>
#include <limits>


using namespace std;


int main() {
    int i = 4;
    double d = 4.0;
    string s = "HackerRank ";


    int a;
    double b;
    string c;
    
    cin >> a >> b;
    getline(cin >> ws, c);

    cout << i + a << endl;

    cout.precision(1);
    cout << fixed << d + b << endl;

    cout << s << c << endl;

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                12
                4.0
                is the best place to learn and practice coding!
    output:     |
                16
                8.0
                HackerRank is the best place to learn and practice coding!
 ******************************************************************************/
