/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 17: More Exceptions"
 -  link:       https://www.hackerrank.com/challenges/30-more-exceptions/problem
 -  hash:       HR19_30DOC_D17

 -  author:     Vitor SRG
 -  version:    1.0 29/03/2019

 -  tags:       implementation class object exception power

 -  language:   C++14
 ******************************************************************************/


#include <cmath>
#include <iostream>
#include <exception>
#include <stdexcept>


using namespace std;


class Calculator {
public:
    int power(int n, int p) {
        if (n < 0 || p < 0)
            throw invalid_argument("n and p should be non-negative");

        if (p == 0)     return 1;

        int t = power(n, p/2);

        if (p%2 == 0)   return t*t;
                        return t*t*n;
        // else if (p > 0) return t*t*n;
        // else            return t*t/p;
    }
};


int main() {
    Calculator myCalculator = Calculator();
    int T,n,p;
    cin>>T;
    while(T-->0){
      if(scanf("%d %d",&n,&p)==2){
         try{
               int ans=myCalculator.power(n,p);
               cout<<ans<<endl; 
         }
         catch(exception& e){
             cout<<e.what()<<endl;
         }
      }
    }   
}


/******************************************************************************
 -  test:
    input:      |
                4
                3 5
                2 4
                -1 -2
                -1 3
    output:     |
                243
                16
                n and p should be non-negative
                n and p should be non-negative
 ******************************************************************************/
