/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 26: Nested Logic"
 -  link:       https://www.hackerrank.com/challenges/30-nested-logic/problem
 -  hash:       HR19_30DOC_D26

 -  author:     Vitor SRG
 -  version:    1.0 05/04/2019

 -  tags:       implementation cases

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int calculate_fine(int dd, int dm, int dy, int rd, int rm, int ry) {
    if (ry < dy)    return 0;
    if (ry > dy)    return 10000;

    if (rm < dm)    return 0;
    if (rm > dm)    return 500*(rm-dm);

    if (rd < dd)    return 0;
    if (rd > dd)    return 15*(rd-dd);

    return 0;
}

int main() {
    int return_day, return_month,   return_year,
        due_day,    due_month,      due_year;

    cin >> return_day   >> return_month >> return_year
        >> due_day      >> due_month    >> due_year;

    cout << calculate_fine(due_day, due_month, due_year,
                           return_day, return_month, return_year) << endl;
    
    return EXIT_SUCCESS;
}


/******************************************************************************
 -  test:
    input:  |
            9 6 2015
            6 6 2015
    output: |
            45
 ******************************************************************************/
