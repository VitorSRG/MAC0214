/******************************************************************************
 -  domain:     HackerRank 2019
 -  contest:    30 Days of Code 2019
 -  problem:    "Day 28: RegEx, Patterns, and Intro to Databases"
 -  link:       https://www.hackerrank.com/challenges/30-regex-patterns/problem
 -  hash:       HR19_30DOC_D28

 -  author:     Vitor SRG
 -  version:    1.0 05/04/2019

 -  tags:       regex sort

 -  language:   C++14
 ******************************************************************************/


#include <bits/stdc++.h>


using namespace std;


int main(int argc, char * argv[]) {
    int n;
    cin >> n;

    vector<string> names;
    names.reserve(n);

    for (int i = 0; i < n; i++) {
        string name, email;
        cin >> name >> email;
        
        if (regex_match(email, regex("^([\\.\\w]+@gmail\\.com)$")))
            names.push_back(name);
    }

    sort(names.begin(), names.end());

    for (int i = 0; i < names.size(); i++)
        cout << names[i] << endl;

    return EXIT_SUCCESS;
}


/******************************************************************************
 -  test:
    input:      |
                6
                riya riya@gmail.com
                julia julia@julia.me
                julia sjulia@gmail.com
                julia julia@gmail.com
                samantha samantha@gmail.com
                tanya tanya@gmail.com
    output:     |
                julia
                julia
                riya
                samantha
                tanya
 -  test:
    input:      |
                30
                riya riya@gmail.com
                julia julia@julia.me
                julia sjulia@gmail.com
                julia julia@gmail.com
                samantha samantha@gmail.com
                tanya tanya@gmail.com
                riya ariya@gmail.com
                julia bjulia@julia.me
                julia csjulia@gmail.com
                julia djulia@gmail.com
                samantha esamantha@gmail.com
                tanya ftanya@gmail.com
                riya riya@live.com
                julia julia@live.com
                julia sjulia@live.com
                julia julia@live.com
                samantha samantha@live.com
                tanya tanya@live.com
                riya ariya@live.com
                julia bjulia@live.com
                julia csjulia@live.com
                julia djulia@live.com
                samantha esamantha@live.com
                tanya ftanya@live.com
                riya gmail@riya.com
                priya priya@gmail.com
                preeti preeti@gmail.com
                alice alice@alicegmail.com
                alice alice@gmail.com
                alice gmail.alice@gmail.com
    output:     |
                alice
                alice
                julia
                julia
                julia
                julia
                preeti
                priya
                riya
                riya
                samantha
                samantha
                tanya
                tanya
 ******************************************************************************/
