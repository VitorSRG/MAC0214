/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 19: Interfaces"
 -  link:       https://www.hackerrank.com/challenges/30-interfaces/problem
 -  hash:       HR19_30DOC_D19

 -  author:     Vitor SRG
 -  version:    1.0 29/03/2019

 -  tags:       implementation class object divisor

 -  language:   C++14
 ******************************************************************************/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;


class AdvancedArithmetic{
public:
    virtual int divisorSum(int n)=0;
};

class Calculator : public AdvancedArithmetic {
public:
    int divisorSum(int n) {
        int s = 0;
        for (int i = 1; i <= n; i++)
            if (n%i == 0)
                s += i;

        return s;
    }
};

int main(){
    int n;
    cin >> n;
    AdvancedArithmetic *myCalculator = new Calculator(); 
    int sum = myCalculator->divisorSum(n);
    cout << "I implemented: AdvancedArithmetic\n" << sum;
    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                6
    output:     |-
                I implemented: AdvancedArithmetic
                12
 ******************************************************************************/
