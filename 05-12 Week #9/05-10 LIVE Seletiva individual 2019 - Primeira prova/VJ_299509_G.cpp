/******************************************************************************
 -  domain:     Virtual Judge
 -  contest:    299509
 -  problem:    G
 -  title:      GCD Extreme
 -  link:       https://vjudge.net/contest/299509#problem/G
 -  hash:       VJ_299509_G

 -  author:     Vitor SRG
 -  version:    1.0 10/05/2019

 -  tags:       gcd query preprocess dp dp-linearithmic euler-totient totient

 -  language:   C++17
 ******************************************************************************/


#pragma GCC optimize ("O3", "Ofast", \
                      "unroll-loops", "rename-registers", \
                      "openmp")


#include <bits/stdc++.h>


using namespace std;


const int MAXN = 1000001;


template <class Value, int N> std::array<Value, N> euler_totient() {
    std::array<Value, N> totient{};

    totient[1] = 1; 
    for (int i = 2; i < N; i++)
        if (!totient[i]) {
            totient[i] = i-1;

            for (int j = (i<<1); j < N; j += i) { 
                if (!totient[j])
                    totient[j] = j;
  
                totient[j] = (totient[j]/i)*(i-1); 
            } 
        }

    return totient;
}

array<long int, MAXN> totient{};
array<long int, MAXN> pair_sum{};


int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    cout.setf(ios::unitbuf);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    totient = euler_totient<long int, MAXN>();

    for (int i = 1; i < MAXN; i++) {
        for (int j = 2; i*j < MAXN; j++)
            pair_sum[i*j] += i*totient[j];

        pair_sum[i] += pair_sum[i-1];
    }

    int n;
    while (cin >> n && n) {
        cout << pair_sum[n] << endl;
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
            10
            100
            200000
    output: |
            67
            13015
            143295493160
 ******************************************************************************/
