/******************************************************************************
 -  domain:     Virtual Judge
 -  contest:    299509
 -  problem:    F
 -  title:      Midnight Cowboy
 -  link:       https://vjudge.net/contest/299509#problem/F
 -  hash:       VJ_299509_F

 -  author:     Vitor SRG
 -  version:    1.0 10/05/2019

 -  tags:       graph float dp dp-tree tree value_iteration operations query dfs

 -  language:   C++17
 ******************************************************************************/


#pragma GCC optimize ("O3", "Ofast", \
                      "unroll-loops", "rename-registers", \
                      "openmp")


#include <bits/stdc++.h>


using namespace std;


const int MAXN = 101;


int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    cout.setf(ios::unitbuf);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<vector<int>> adj(MAXN, vector<int>());
    vector<double> prob(MAXN);
    vector<double> prob_next(MAXN);

    int n;
    while (cin >> n && !cin.eof()) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--; c--;

        for (int i = 0; i < n; i++)
            adj[i].clear();


        for (int i = 0; i < n-1; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        fill(prob.begin(), prob.begin()+n, 0);
        for (int i = 0; i < 6*6*10*n; i++) {
            fill(prob_next.begin(), prob_next.begin()+n, 0);
            prob[b] = 1;
            prob[c] = 0;

            for (int u = 0; u < n; u++)
                if (u != b && u != c) {
                    for (int v : adj[u])
                        prob_next[u] += prob[v];
                    prob_next[u] /= adj[u].size();
                }

            copy(prob_next.begin(), prob_next.begin()+n, prob.begin());
        }

        cout.setf(ios::fixed);
        cout.precision(6);
        cout << prob[a] << endl;
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
            4 1 2 3
            1 4
            2 4
            3 4
            5 3 1 5
            1 2
            2 3
            3 4
            4 5
    output: |
            0.500000
            0.500000
 ******************************************************************************/
