/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 12: Inheritance"
 -  link:       https://www.hackerrank.com/challenges/30-inheritance/problem
 -  hash:       HR19_30DOC_D12

 -  author:     Vitor SRG
 -  version:    1.0 29/03/2019

 -  tags:       implementation class object

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


class Person {
protected:
    string firstName;
    string lastName;
    int id;

public:
    Person(string firstName, string lastName, int identification) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->id = identification;
    }

    void printPerson() {
        cout<< "Name: "<< lastName << ", "<< firstName <<"\nID: "<< id << "\n"; 
    }
};

class Student : public Person {
private:
    vector<int> testScores;  
public:
    Student(string firstName, string lastName, int id, vector<int> testScores) :
    Person(firstName, lastName, id),
    testScores(testScores) {

    }

    char calculate() {
        double avg = accumulate(testScores.begin(), testScores.end(), 0)
                     /(double) testScores.size();

        if      (avg < 40)  return 'T';
        else if (avg < 55)  return 'D';
        else if (avg < 70)  return 'P';
        else if (avg < 80)  return 'A';
        else if (avg < 90)  return 'E';
        else                return 'O';
    }
};

int main() {
    string firstName;
    string lastName;
    int id;
    int numScores;
    cin >> firstName >> lastName >> id >> numScores;
    vector<int> scores;
    for(int i = 0; i < numScores; i++){
        int tmpScore;
        cin >> tmpScore;
        scores.push_back(tmpScore);
    }
    Student* s = new Student(firstName, lastName, id, scores);
    s->printPerson();
    cout << "Grade: " << s->calculate() << "\n";
    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                Heraldo Memelli 8135627
                2
                100 80
    output:     |
                Name: Memelli, Heraldo
                ID: 8135627
                Grade: O
 ******************************************************************************/
