/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 14: Scope"
 -  link:       https://www.hackerrank.com/challenges/30-scope/problem
 -  hash:       HR19_30DOC_D14

 -  author:     Vitor SRG
 -  version:    1.0 29/03/2019

 -  tags:       implementation class object

 -  language:   C++14
 ******************************************************************************/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;


class Difference {
private:
    vector<int> elements;
  
public:
    int maximumDifference;

    Difference(vector<int> elements) :
    elements(elements) {
    }

    void computeDifference() {
        maximumDifference = *max_element(elements.begin(), elements.end())
                            - *min_element(elements.begin(), elements.end());
    }

};


int main() {
    int N;
    cin >> N;
    
    vector<int> a;
    
    for (int i = 0; i < N; i++) {
        int e;
        cin >> e;
        
        a.push_back(e);
    }
    
    Difference d(a);
    
    d.computeDifference();
    
    cout << d.maximumDifference;
    
    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                3
                1 2 5
    output:     >-
                4
 ******************************************************************************/
