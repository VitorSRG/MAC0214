/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 2: Operators"
 -  link:       https://www.hackerrank.com/challenges/30-operators/problem
 -  hash:       HR19_30DOC_D02

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


void solve(double meal_cost, int tip_percent, int tax_percent) {
    cout << round(meal_cost*(100+tip_percent+tax_percent)/100) << endl;
}


int main() {
    double meal_cost;
    cin >> meal_cost;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int tip_percent;
    cin >> tip_percent;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int tax_percent;
    cin >> tax_percent;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    solve(meal_cost, tip_percent, tax_percent);

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                12.00
                20
                8
    output:     |
                15
 ******************************************************************************/
