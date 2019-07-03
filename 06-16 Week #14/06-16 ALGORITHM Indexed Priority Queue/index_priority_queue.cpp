/******************************************************************************
 *  @domain     Data Structure
 *  @title      Indexed Priority Queue
 *  @link       https://algs4.cs.princeton.edu/24pq/IndexMinPQ.java.html
 *  @link       https://github.com/Mr-Awakened/algorithmcpp/blob/master/algorithm/indexed_priority_queue.h
 *  @hash       indexed_priority_queue
 * 
 *  @author     Vitor SRG
 *  @version    1.0 15/04/2019
 * 
 *  @tags       #indexed_priority_queue
 ******************************************************************************/

// #include <bits/stdc++.h>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

#define DEBUG

#ifdef DEBUG
#define ASSERT(expr, msg) assert(expr && msg);
#else
#define ASSERT(expr, msg)
#endif


// template <
//     class Key, 
//     class Value, 
//     class Vector = std::vector<Value>,
//     class UMap = std::unordered_map<Key, Value>, 
//     class Less = std::less<class Vector::value_type>
// > class IndexMinPQ;

#pragma push_macro("min")
#undef min
template<
    class Value,
    class Less = std::less<Value>
> class indexed_priority_queue {
    public:
        int max_n_;
        int n_;
        std::vector<int> pq_;
        std::vector<int> qp_;
        std::vector<Value> vals_;


        indexed_priority_queue() = delete;
        indexed_priority_queue(const indexed_priority_queue &) = default;
        indexed_priority_queue(indexed_priority_queue &&) noexcept = default;
        indexed_priority_queue &operator=(const indexed_priority_queue &) = default;
        indexed_priority_queue &operator=(indexed_priority_queue &&) noexcept = default;
        ~indexed_priority_queue() = default;


        indexed_priority_queue(int max_n) :
            max_n_(max_n), 
            n_(0), 
            pq_(std::vector<int>(max_n+1, -1)), 
            qp_(std::vector<int>(max_n+1, -1)), 
            vals_(std::vector<Value>(max_n, NULL)) {
        }


        inline void swap_(int i, int j) {
            std::swap(pq_[i], pq_[j]);
            qp_[static_cast<int>(pq_[i])] = static_cast<int>(i);
            qp_[static_cast<int>(pq_[j])] = static_cast<int>(j);
        }

        inline bool less_(int i, int j) const {
            return Less()(vals_[pq_[i]], vals_[pq_[j]]);
        }

        void swim_(int k) {
            while (k > 1 && !less_(k / 2, k)) {
                swap_(k, k / 2);
                k = k / 2;
            }
        }

        void sink_(int k) {
            while (2 * k <= n_) {
                int j = 2 * k;
                if (j < n_ && !less_(j, j + 1)) ++j;
                if (less_(k, j)) break;
                swap_(k, j);
                k = j;
            }
        }

        inline bool empty() const {
            return n_ == 0;
        }

        inline bool contains(int i) const {
            ASSERT(0 <= i && i < max_n_, "index out of range");
            
            return qp_[i] != -1;
        }

        inline int size() const {
            return n_;
        }

        void insert(int i, const Value &val) {
            ASSERT(0 <= i && i < max_n_, "index out of range");
            ASSERT(!contains(i), "index is already in the priority queue");
            
            n_++;
            vals_[i] = val;
            qp_[i] = static_cast<int>(n_);
            pq_[n_] = static_cast<int>(i);
            swim_(n_);
        }

        void update(int i, const Value& val) {
            ASSERT(0 <= i && i < max_n_, "index out of range");
            ASSERT(contains(i), "index is not in the priority queue");

            vals_[i] = val;
            swim_(qp_[i]);
            sink_(qp_[i]);
        }

        inline void push(int i, const Value &val) {
            if (contains(i)) update(i, val);
            else             insert(i, val);
        }

        Value operator[](int i) const {
            ASSERT(0 <= i && i < max_n_, "index out of range");
            ASSERT(contains(i), "index is not in the priority queue");

            return vals_[i];
        }

        inline Value top() const {
            return vals_[pq_[1]];
        }

        inline int topkey() const {
            ASSERT(n_ != 0, "priority queue underflow");
            
            return pq_[1];
        }

        std::pair<int, Value> topitem() const {
            return std::make_pair(pq_[1], vals_[pq_[1]]);
        }

        inline Value pop() {
            return pop(topkey());
        }

        inline Value pop(int i) {
            return popitem(i)[1];
        }

        inline int popkey() {
            return popkey(topkey());
        }

        inline int popkey(int i) {
            return popitem(i)[0];
        }

        inline std::pair<int, Value> popitem() {
            return popitem(topkey());
        }

        inline std::pair<int, Value> popitem(int i) {
            ASSERT(0 <= i && i < max_n_, "index out of range");
            ASSERT(contains(i), "index is not in the priority queue");

            std::pair<int, Value> item = std::make_pair(i, vals_[i]);

            int index = qp_[i];
            swap_(index, n_--);
            swim_(index);
            sink_(index);
            vals_[i] = NULL;
            qp_[i] = -1;

            return item;
        }
};
#pragma pop_macro("min")

using namespace std;


int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    cout.setf(ios::unitbuf);
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    vector<int> data{1, 3, 5, 7, 2, 4, 6};
    // i:            0, 1, 2, 3, 4, 5, 6
    // min:          0, 2, 4, 6, 1, 3, 5
    // max:          6, 4, 2, 0, 5, 3, 1
    int n = data.size();
    vector<int> locs(n, -1);

    for (int i = 0; i < n; i++)
        locs[data[i]] = i;

    for (int a : data)
        cout << locs[a] << ":" << a << " ";
    cout << endl;

    indexed_priority_queue<int> iminpq = indexed_priority_queue<int>(n);
    for (int i = 0; i < n; i++)
        iminpq.push(i, data[i]);

    for (int i = 0; i < n; i++) {
        int key, value;
        tie(key, value) = iminpq.popitem();
        cout << key << ":" << value << " ";
    }
    cout << endl;

    indexed_priority_queue<int, greater<int>> imaxpq = indexed_priority_queue<int, greater<int>>(n);
    for (int i = 0; i < n; i++)
        imaxpq.push(i, data[i]);

    for (int i = 0; i < n; i++) {
        int key, value;
        tie(key, value) = imaxpq.popitem();
        cout << key << ":" << value << " ";
    }
    cout << endl;
    
    return EXIT_SUCCESS;
}

int unit_test(int argc, char* argv[]) {
    return EXIT_SUCCESS;
}

/******************************************************************************
 *  @tests      defaults m: 256.mb, t: 1.s, q: true
 * 
 *  @tests      literal "", \
                        "0:1 1:3 2:5 3:7 4:2 5:4 6:6\n" \
                        "0:1 4:2 1:3 5:4 2:5 6:6 3:7\n" \
                        "3:7 6:6 2:5 5:4 1:3 4:2 0:1\n"
 ******************************************************************************/
