/******************************************************************************
 -  domain:     Virtual Judge
 -  contest:    299509
 -  problem:    A
 -  title:      Cats and Dogs
 -  link:       https://vjudge.net/contest/299509#problem/A
 -  hash:       VJ_299509_A

 -  author:     Vitor SRG
 -  version:    1.0 10/05/2019

 -  tags:       implementation tests online

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

    for (int ti = 0; ti < t; ti++) {
        long long cats, dogs, legs;
        cin >> cats >> dogs >> legs;

        if (legs < 4*dogs
            || legs > 4*cats + 4*dogs
            || legs % 4 != 0
            || legs < 4*dogs + 4*(cats - 2*dogs))
            cout << "no" << endl;
        else
            cout << "yes" << endl;
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
            3
            1 1 8
            1 1 4
            1 1 2
    output: |
            yes
            yes
            no
 ******************************************************************************/
