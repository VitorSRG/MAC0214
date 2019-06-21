/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 4: Class vs. Instance"
 -  link:       https://www.hackerrank.com/challenges/30-class-vs-instance/problem
 -  hash:       HR19_30DOC_D04

 -  author:     Vitor SRG
 -  version:    1.0 22/03/2019

 -  tags:       implementation object

 -  language:   C++14
 ******************************************************************************/


#include <iostream>


using namespace std;


class Person {
    public:
        int age;
        Person(int initialAge);
        void amIOld();
        void yearPasses();
    };

    Person::Person(int initialAge) {
        if (initialAge < 0) {
            age = 0;
            cout << "Age is not valid, setting age to 0." << endl;
        }
        else {
            age = initialAge;
        }
    }

    void Person::amIOld() {
        if (age < 13)       cout << "You are young." << endl;
        else if (age < 18)  cout << "You are a teenager." << endl;
        else                cout << "You are old." << endl;
    }

    void Person::yearPasses() {
        age++;
    }


int main() {
    int t;
    int age;
    cin >> t;
    for(int i=0; i < t; i++) {
        cin >> age;
        Person p(age);
        p.amIOld();
        for(int j=0; j < 3; j++) {
            p.yearPasses(); 
        }
        p.amIOld();
      
        cout << '\n';
    }

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                4
                -1
                10
                16
                18
    output:     |+
                Age is not valid, setting age to 0.
                You are young.
                You are young.

                You are young.
                You are a teenager.

                You are a teenager.
                You are old.

                You are old.
                You are old.

 ******************************************************************************/
