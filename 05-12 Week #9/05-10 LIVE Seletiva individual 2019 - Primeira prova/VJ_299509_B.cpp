/******************************************************************************
 -  domain:     Virtual Judge
 -  contest:    299509
 -  problem:    B
 -  title:      Bnansi's Cobweb
 -  link:       https://vjudge.net/contest/299509#problem/B
 -  hash:       VJ_299509_B

 -  author:     Vitor SRG
 -  version:    1.0 10/05/2019

 -  tags:       graph connectivity operation online query

 -  language:   C++17
 ******************************************************************************/


#pragma GCC optimize ("O3", "Ofast", \
                      "unroll-loops", "rename-registers", \
                      "openmp")


#include <bits/stdc++.h>


using namespace std;


const int MAXN = 100001;
const int MAXM = 100001;


vector<unordered_set<int>> adj(MAXN, unordered_set<int>());
vector<pair<int, int>> edges(MAXN);
array<bool, MAXN> visited;


int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    cout.setf(ios::unitbuf);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);

        edges[i] = make_pair(u, v);
    }

    int component_count = 0;

    fill(visited.begin(), visited.begin()+n, false);
    for (int u = 0; u < n; u++)
        if (!visited[u]) {
            component_count++;
            stack<int> stack;

            stack.push(u);
            while (!stack.empty()) {
                int v = stack.top();
                stack.pop();
                visited[v] = true;

                for (int w : adj[v])
                    if (!visited[w])
                        stack.push(w);
            }
        }

    int q;
    cin >> q;
    for (int qi = 0; qi < q; qi++) {
        int e, u, v;
        cin >> e;
        e--;
        tie(u, v) = edges[e];

        adj[u].erase(v);
        adj[v].erase(u);

        fill(visited.begin(), visited.begin()+n, false);
        stack<int> stack;

        stack.push(u);
        while (!stack.empty()) {
            int w = stack.top();
            stack.pop();
            visited[w] = true;

            for (int z : adj[w])
                if (!visited[z])
                    stack.push(z);
        }

        if (!visited[v])
            component_count++;

        cout << component_count;
        if (qi < q-1) cout << ' ';
        else          cout << endl;
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
            4 4
            1 2
            2 3
            1 3
            3 4
            3
            2 4 3
    output: |
            1 2 3

 -  test:
    input:  |
            3 1
            1 2
            1
            1
    output: |
            3
 ******************************************************************************/
