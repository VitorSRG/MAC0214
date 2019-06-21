/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 13: Abstract Classes"
 -  link:       https://www.hackerrank.com/challenges/30-abstract-classes/problem
 -  hash:       HR19_30DOC_D13

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
#include <string>


using namespace std;


class Book {
protected:
    string title;
    string author;
public:
    Book(string t,string a) {
        title=t;
        author=a;
    }

    virtual void display()=0;
};

class MyBook : public Book {
private:
    int price;
public:
    MyBook(string title, string author, int price) :
    Book(title, author),
    price(price) {

    }

    void display() {
        cout << "Title: "  << title  << endl;
        cout << "Author: " << author << endl;
        cout << "Price: "  << price  << endl;
    }
};

int main() {
    string title, author;
    int price;

    getline(cin, title);
    getline(cin, author);
    cin >> price;

    MyBook novel(title, author, price);
    novel.display();

    return 0;
}


/******************************************************************************
 -  test:
    input:      |
                The Alchemist
                Paulo Coelho
                248
    output:     |
                Title: The Alchemist
                Author: Paulo Coelho
                Price: 248
 ******************************************************************************/
