/******************************************************************************
 -  domain:     Kattis
 -  contest:    VTEX Code Cup 2019
 -  problem:    C
 -  title:      Conveyor Belt Inspection
 -  link:       https://vtexcc19.kattis.com/problems/vtexcc19.automaticlight
 -  hash:       VTEXCC19_1_C

 -  author:     Vitor SRG
 -  version:    1.0 11/05/2019

 -  tags:       graph dfs cycle dp dp-graph grid sum

 -  language:   C++17
 ******************************************************************************/

#pragma GCC optimize ("O3", "Ofast", \
                      "unroll-loops", "rename-registers", \
                      "openmp")


#include <bits/stdc++.h>


using namespace std;


const int MAXN = 10e3;
const int MAXM = 10e3;

char direction[MAXN][MAXM];
int walks[MAXN][MAXM];
bool visited_cicle[MAXN][MAXM];
bool visited[MAXN][MAXM];


int walk_cicle(int i, int j, int n, int m, int depth) {
    if ( visited_cicle[i][j]) {
        visited_cicle[i][j] = false;
        return depth;
    }

    visited_cicle[i][j] = true;
    int length;
    switch (direction[i][j]) {
        case 'N': length = walk_cicle(i-1, j  , n, m, depth+1); break;
        case 'E': length = walk_cicle(i  , j+1, n, m, depth+1); break;
        case 'S': length = walk_cicle(i+1, j  , n, m, depth+1); break;
        case 'W': length = walk_cicle(i  , j-1, n, m, depth+1); break;
    }

    visited_cicle[i][j] = false;
    walks[i][j] = length;
    return walks[i][j];
}

int walk(int i, int j, int n, int m) {
    if (i < 0 || i >= n || j < 0 || j >= m)
        return 0;
    if (walks[i][j] > 0)
        return walks[i][j];

    if (visited[i][j]) {
        walk_cicle(i, j, n, m, 0);
        return 0;
    }

    visited[i][j] = true;
    int length;
    switch (direction[i][j]) {
        case 'N': length = walk(i-1, j  , n, m); break;
        case 'E': length = walk(i  , j+1, n, m); break;
        case 'S': length = walk(i+1, j  , n, m); break;
        case 'W': length = walk(i  , j-1, n, m); break;
    }

    visited[i][j] = false;
    if (walks[i][j] == 0)
        walks[i][j] = 1 + length;
    return walks[i][j];
}

int main(int argc, char* argv[]) {
    // setbuf(stdout, NULL);
    // cout.setf(ios::unitbuf);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> direction[i][j];

    int walk_sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            walk_sum += walk(i, j, n, m);

    cout << walk_sum << endl;

    return EXIT_SUCCESS;
}

int unit_test(int argc, char* argv[]) {
    return EXIT_SUCCESS;
}

/******************************************************************************
 -  time:   2s
 -  memory: 1024mb

 -  test:
    input:  |
            1 3
            WWW
    output: |
            6

 -  test:
    input:  |
            3 3
            EES
            NSS
            NWW
    output: |
            73

 -  test:
    input:  |
            3 3
            ESN
            NWW
            NNW
    output: |
            38
 ******************************************************************************/
