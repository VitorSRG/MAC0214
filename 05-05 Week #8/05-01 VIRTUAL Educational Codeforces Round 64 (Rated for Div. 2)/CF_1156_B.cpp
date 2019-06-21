/******************************************************************************
 -  domain:     Codeforces
 -  contest:    1156
 -  problem:    B
 -  title:      Ugly Pairs
 -  link:       https://codeforces.com/contest/1156/problem/B
 -  hash:       CF_1156_B

 -  author:     Vitor SRG
 -  version:    1.0 01/05/2019

 -  tags:       implementation sort count greedy string

 -  language:   C++17
 ******************************************************************************/


#pragma GCC optimize ("O3", "Ofast", \
                      "unroll-loops", "rename-registers", \
                      "openmp")


#include <bits/stdc++.h>


using namespace std;


int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    cout.setf(ios::unitbuf);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;

    string s;
    int alphacount[26];
    vector<int> letters;
    letters.reserve(26);
    for (int ti = 0; ti < t; ti++) {
        cin >> s;
        fill(alphacount, alphacount+26, 0);
        letters.clear();

        for (char c : s) {
            c -= 'a';
            if (!alphacount[c])
                letters.push_back(c);
            alphacount[c]++;
        }
        sort(letters.begin(), letters.end());

        if (letters.size() == 2 && letters[0] == letters[1]-1
            || letters.size() == 3 && letters[0] == letters[1]-1
                                   && letters[1] == letters[2]-1) {
            cout << "No answer" << endl;
            continue;
        }

        if (letters.size() == 3 && letters[0] == letters[1]-1) {
            swap(letters[0], letters[2]);
            swap(letters[1], letters[2]);
        }

        int mid = letters.size()/2;
        for (int i = 0; i < mid; i++) {
            while (alphacount[letters[mid+i]]--)
                cout << (char) (letters[mid+i]+'a');
            while (alphacount[letters[i]]--)
                cout << (char) (letters[i]+'a');
        }

        if (2*mid < letters.size())
            while (alphacount[letters[2*mid]]--)
                cout << (char) (letters[2*mid]+'a');

        cout << endl;
    }

    return EXIT_SUCCESS;
}

int unit_test(int argc, char* argv[]) {
    return EXIT_SUCCESS;
}


/******************************************************************************
 -  time:   1s
 -  memory: 256mb

 -  test:
    input:  |
            4
            abcd
            gg
            codeforces
            abaca
    output: |
            cadb
            gg
            codfoerces
            No answer
 ******************************************************************************/
