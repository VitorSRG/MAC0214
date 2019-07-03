/******************************************************************************
 *  @domain     Data Structure
 *  @title      Binary Indexed Tree
 *  @link       https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
 *  @link       https://codeforces.com/blog/entry/61364
 *  @hash       #binary_indexed_tree
 * 
 *  @author     Vitor SRG
 *  @version    1.0 15/04/2019
 * 
 *  @tags       #binary_indexed_tree
 ******************************************************************************/

// #include <bits/stdc++.h>
#include <cassert>
#include <climits>
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
//     class Value, 
//     class Vector = std::vector<Value>, 
//     class Reduce = std::plus<class Vector::value_type>
// > class BITree;

template<class Value, typename Aggregate = std::plus<Value>>
class binary_indexed_tree {
    public:
        int n_;
        Value id_;
        std::vector<Value> bit_;
        std::vector<Value> vals_;
        Aggregate agg_;


        binary_indexed_tree() = delete;
        binary_indexed_tree(const binary_indexed_tree &) = default;
        binary_indexed_tree(binary_indexed_tree &&) noexcept = default;
        binary_indexed_tree &operator=(const binary_indexed_tree &) = default;
        binary_indexed_tree &operator=(binary_indexed_tree &&) noexcept = default;
        ~binary_indexed_tree() = default;


        inline binary_indexed_tree(std::vector<Value>& arr) : 
            binary_indexed_tree(arr.data(), arr.size(), Aggregate(), NULL) {
        }

        inline binary_indexed_tree(std::vector<Value>& arr, int n) : 
            binary_indexed_tree(arr.data(), n, Aggregate(), NULL) {
        }

        inline binary_indexed_tree(Value arr[], int n) : 
            binary_indexed_tree(arr, n, Aggregate(), NULL) {
        }

        inline binary_indexed_tree(std::vector<Value>& arr,
                                   const Aggregate agg,
                                   const Value id) : 
            binary_indexed_tree(arr.data(), arr.size(), agg, id) {
        }

        inline binary_indexed_tree(std::vector<Value>& arr, int n,
                                   const Aggregate agg,
                                   const Value id) : 
            binary_indexed_tree(arr.data(), n, agg, id) {
        }

        binary_indexed_tree(Value arr[], int n, 
                            const Aggregate agg,
                            const Value id) :
            n_(n),
            bit_(std::vector<Value>(n+1, id)),
            vals_(std::vector<Value>(arr, arr+n)),
            agg_(agg),
            id_(id) {
            for (int i = 0; i < n; i++)
                update_(i, vals_[i]);
        }


        void update_(int i, const Value val) {
            i += 1;

            while (i <= n_) {
                bit_[i] = agg_(bit_[i], val);
                i += i & -i;
            } 
        }

        Value operator[](int i) const {
            ASSERT(0 <= i && i < n_, "index out of range");

            return vals_[i];
        }

        inline Value preffix(int i) const {
            return preffix(i, id_);
        }

        Value preffix(int i, const Value identity) const {
            ASSERT(0 <= i && i < n_, "index out of range");
            i = i + 1; 
        
            Value agg = identity;
            while (i > 0)  {
                agg = agg_(agg, bit_[i]);
                i -= i & -i; 
            }

            return agg; 
        }

        inline void update(int i, const Value val) { 
            update(i, val, std::negate<Value>());
        }

        template<class Negate = std::negate<Value>> 
        void update(int i, const Value val, const Negate neg) { 
            ASSERT(0 <= i && i < n_, "index out of range");

            Negate neg_ = Negate(neg);

            update_(i, neg_(vals_[i]));
            vals_[i] = val;
            update_(i, val);
        }

        inline int pow_(int b, int e) const {
            if (e == 0) return 1;
            if (e == 1) return b;

            int tmp = pow_(b, e/2);
            if (e%2 == 0) return tmp*tmp;
            else          return b*tmp*tmp;
        }

        inline int log2_(unsigned int i) const {
            #ifdef DEBUG
            unsigned int j = i;
            #endif
            register unsigned int r;
            register unsigned int shift;

            r =     (i > 0xFFFF) << 4; i >>= r;
            shift = (i > 0xFF  ) << 3; i >>= shift; r |= shift;
            shift = (i > 0xF   ) << 2; i >>= shift; r |= shift;
            shift = (i > 0x3   ) << 1; i >>= shift; r |= shift;
                                                    r |= (i >> 1);

            ASSERT(pow_(2, r) <= j && j <= pow_(2, r+1), "wrong log2");
            // int r = 0;
            // while (index >>= 1) r++;
            return r;
        }

        inline int search_leftmost(const Value q) const {
            return search_leftmost(q, id_, std::less<Value>());
        }

        template<class Less = std::less<Value>>
        int search_leftmost(const Value q, const Value id, const Less less) const {
            Less less_ = Less(less);
            Value agg = id;
            int i = 0;
            for (int r = log2_(n_); r >= 0; r--) {
                int l = i + (1 << r);
                Value v = agg_(agg, bit_[l]);
                if (l < n_ && less_(v, q)) {
                    agg = v;
                    i = l;
                }
            }
            
            return i;
        }

};

using namespace std;


int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    cout.setf(ios::unitbuf);
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    vector<int> data{1, 2, 3, 4, 5, 6, 7};
    int n = data.size();

    for (int i = 0; i < n; i++)
        cout << i << "\t";
    cout << endl;
    for (int a : data)
        cout << a << "\t";
    cout << endl;
    cout << endl;


    binary_indexed_tree<int> bitree(data);
    
    for (int i = 0; i < n; i++)
        cout << bitree[i] << "\t";
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << bitree.preffix(i) << "\t";
    cout << endl;
    cout << endl;

    bitree.update(2, 4);
    bitree.update(4, 6);
    bitree.update(6, 8);
    
    for (int i = 0; i < n; i++)
        cout << bitree[i] << "\t";
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << bitree.preffix(i) << "\t";
    cout << endl;
    cout << endl;

    for (int i = 0; i < n; i++)
        cout << 2*i+1 << "\t";
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << bitree.search_leftmost(2*i+1) << "\t";
    cout << endl;
    cout << endl;

    vector<int> sequence{2, 1, 0, 3, 4, 1, 2, 3, 8, 3, 4};
    int l = sequence.size();

    auto maximum = [](int a, int b) { return max(a, b); };
    binary_indexed_tree<int, decltype(maximum)> bimax(sequence, maximum, INT_MIN);

    for (int i = 0; i < l; i++)
        cout << i << "\t";
    cout << endl;
    cout << endl;
    for (int i = 0; i < l; i++)
        cout << bimax[i] << "\t";
    cout << endl;
    for (int i = 0; i < l; i++)
        cout << bimax.preffix(i) << "\t";
    cout << endl;
    cout << endl;


    return EXIT_SUCCESS;
}

int unit_test(int argc, char* argv[]) {
    return EXIT_SUCCESS;
}

/******************************************************************************
 *  @tests      defaults m: 256.mb, t: 1.s
 * 
 *  @tests      literal "", \
                        "0\t1\t2\t3\t4\t5\t6\t\n" \
                        "1\t2\t3\t4\t5\t6\t7\t\n\n" \
                        "1\t2\t3\t4\t5\t6\t7\t\n" \
                        "1\t3\t6\t10\t15\t21\t28\t\n\n" \
                        "1\t2\t4\t4\t6\t6\t8\t\n" \
                        "1\t3\t7\t11\t17\t23\t31\t\n\n" \
                        "1\t3\t5\t7\t9\t11\t13\t\n" \
                        "0\t1\t2\t2\t3\t3\t4\t\n\n" \
                        "0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t\n\n" \
                        "2\t1\t0\t3\t4\t1\t2\t3\t8\t3\t4\t\n" \
                        "2\t2\t2\t3\t4\t4\t4\t4\t8\t8\t8\t\n\n"
 ******************************************************************************/

