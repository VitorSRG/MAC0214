/******************************************************************************
 -  domain:     Kattis
 -  contest:    VTEX Code Cup 2019
 -  problem:    G
 -  title:      Punctual Chefs
 -  link:       https://vtexcc19.kattis.com/problems/vtexcc19.punctualchefs
 -  hash:       VTEXCC19_1_G

 -  author:     Vitor SRG
 -  version:    1.0 11/05/2019

 -  tags:       simulation events pqueue sort comparator greedy

 -  language:   C++17
 ******************************************************************************/

#pragma GCC optimize ("O3", "Ofast", \
                      "unroll-loops", "rename-registers", \
                      "openmp")


#include <bits/stdc++.h>


using namespace std;


const int MAXN = 100000;
const int MAXK = 10000;

struct Customer {
    int t;
    int d;
    int i;
    char c;
    int f;
};

bool customer_cmp(const Customer& a, const Customer& b) {
    return a.t < b.t || (a.t == b.t && a.i < b.i);
}

vector<Customer> customers(MAXN);

int main(int argc, char* argv[]) {
    // setbuf(stdout, NULL);
    // cout.setf(ios::unitbuf);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> customers[i].t >> customers[i].d;
        customers[i].i = i;
    }


    priority_queue<pair<int, int>, vector<pair<int, int>>, 
                   greater<pair<int, int>>> events;
    for (int i = 0; i < n; i++)
        events.push(make_pair(customers[i].t, customers[i].i));

    int ALEAVE = -2, BLEAVE = -1;

    int adue = 0, bdue = 0;
    int aline = 0, bline = 0;
    while (!events.empty()) {
        int t, i;
        tie(t, i) = events.top();
        events.pop();

        if (i == ALEAVE) {
            aline--;
        } else if (i == BLEAVE) {
            bline--;
        } if (i >= 0 && i < n) {
            Customer& customer = customers[i];
            if (adue <= t) {
                customer.c = 'A';
                customer.f = t+customer.d;
                adue = t+customer.d;
                aline++;
                events.push(make_pair(adue, ALEAVE));
            } else if (bdue <= t) {
                customer.c = 'B';
                customer.f = t+k*customer.d;
                bdue = t+k*customer.d;
                bline++;
                events.push(make_pair(bdue, BLEAVE));
            } else if (aline <= bline) {
                customer.c = 'A';
                customer.f = adue+customer.d;
                adue = adue+customer.d;
                aline++;
                events.push(make_pair(adue, ALEAVE));
            } else {
                customer.c = 'B';
                customer.f = bdue+k*customer.d;
                bdue = bdue+k*customer.d;
                bline++;
                events.push(make_pair(bdue, BLEAVE));
            }
        }
    }

    for (int i = 0; i < n; i++)
        cout << customers[i].c << " " << customers[i].f << endl;

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
            4 2
            0 10
            6 6
            1 5
            10 1
    output: |
            A 10
            A 16
            B 11
            A 17

 -  test:
    input:  |
            4 2
            0 10
            6 6
            1 5
            10 1
    output: |
            A 10
            A 16
            B 11
            A 17

 -  test:
    input:  |
            4 2
            0 10
            6 6
            1 5
            9 1
    output: |
            A 10
            A 16
            B 11
            B 13

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
            3 10
            0 1
            0 1
            0 1
    output: |
            A 1
            B 10
            A 2
 ******************************************************************************/
