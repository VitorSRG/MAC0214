/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 21: Generics"
 -  link:       https://www.hackerrank.com/challenges/30-generics/problem
 -  hash:       HR19_30DOC_D21

 -  author:     Vitor SRG
 -  version:    1.0 05/04/2019

 -  tags:       generics array

 -  language:   C++14
 ******************************************************************************/


#include <iostream>
#include <vector>
#include <string>


using namespace std;


template<class Type>
void printArray(vector<Type> arr) {
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << endl;
}

int main() {
    int n;
        
    cin >> n;
    vector<int> int_vector(n);
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        int_vector[i] = value;
    }
        
    cin >> n;
    vector<string> string_vector(n);
    for (int i = 0; i < n; i++) {
        string value;
        cin >> value;
        string_vector[i] = value;
    }

    printArray<int>(int_vector);
    printArray<string>(string_vector);

    return 0;
}


/******************************************************************************
 -  test:
    input:  |
            3
            1
            2
            3
            2
            Hello
            World
    output: |
            1
            2
            3
            Hello
            World
 ******************************************************************************/
