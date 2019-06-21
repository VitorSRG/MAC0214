/******************************************************************************
 -  domain:     Codeforces
 -  contest:    1156
 -  problem:    A
 -  title:      Inscribed Figures
 -  link:       https://codeforces.com/contest/1156/problem/A
 -  hash:       CF_1156_A

 -  author:     Vitor SRG
 -  version:    1.0 01/05/2019

 -  tags:       implementation geometry cases online

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

    int n;
    cin >> n;

    int intersections[][3] = {{-1,  3,  4},
                              { 3, -1, -1},
                              { 4, -1, -1}};

    int distinct = 0;
    int a1 = 0, a2 = 0, a3 = 0;
    for (int i = 0; i < n; i++) {
        cin >> a3;

        if (a2) {
            int inter = intersections[a2-1][a3-1];

            if (inter < 0) {
                cout << "Infinite" << endl;
                return EXIT_SUCCESS;
            }

            if (a1 && a1 == 3 && a2 == 1 && a3 == 2)
                inter -= 1;

            distinct += inter;
        }

        a1 = a2;
        a2 = a3;
    }


    cout << "Finite" << endl;
    cout << distinct << endl;


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
            2 1 3
    output: |
            Finite
            7

 -  test:
    input:  |
            3
            1 2 3
    output: |
            Infinite
 ******************************************************************************/
