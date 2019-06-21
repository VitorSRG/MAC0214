/******************************************************************************
 -  domain:     Kattis
 -  contest:    VTEX Code Cup 2019
 -  problem:    A
 -  title:      Automatic Light
 -  link:       https://vtexcc19.kattis.com/problems/vtexcc19.automaticlight
 -  hash:       VTEXCC19_1_C

 -  author:     Vitor SRG
 -  version:    1.0 11/05/2019

 -  tags:       implementation greedy sort

 -  language:   C++17
 ******************************************************************************/

#pragma GCC optimize ("O3", "Ofast", \
                      "unroll-loops", "rename-registers", \
                      "openmp")


#include <bits/stdc++.h>


using namespace std;


const int MAXN = 10e3;


int main(int argc, char* argv[]) {
    // setbuf(stdout, NULL);
    // cout.setf(ios::unitbuf);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> in(n, 0);
    vector<int> out(n, 0);

    for (int i = 0; i < n; i++)
        cin >> in[i] >> out[i];

    sort(in.begin(), in.end(), less<int>());
    sort(out.begin(), out.end(), less<int>());

    int mininterval = INT_MIN;
    for (int i = -1, j = -1, inside = 0; j < n-1; ) {
        if (inside == 0) {
            i++;
            inside++;
        } else if (i < n-1 && in[i+1] < out[j+1]) {
            i++;
            inside++;
        } else {
            mininterval = max(mininterval, out[j+1]-in[i]);
            j++;
            inside--;
        }
    }

    // for (int i = 0; i < n; i++)
    //     cout << in[i] << " " << out[i] << endl;
    cout << mininterval << endl;

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
            1
            5 278
    output: |
            273

 -  test:
    input:  |
            4
            0 10
            4 6
            11 14
    output: |
            12 15
            6
 ******************************************************************************/
