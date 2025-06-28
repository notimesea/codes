//
// Created by Evgeny Savinov on 09/01/2017.
//

#include <bits/stdc++.h>

// Simple open-addressing hash map for integer keys.
//#pragma GCC optimize ("O3")

using namespace std;

template<class K, class V, int D = 20, K to_xor = 10778448979374848739ull, K to_mul = 14774228369217122871ull>
struct HashMap {
    enum State {
        free,
        used
    };
    struct Node {
        K key;
        V value{V()};
        State state{State::free};
    };

    Node nodes[1 << D];
    size_t size;

    size_t hash(const K& k) const {
        return ((k ^ to_xor) * to_mul) & ((1 << D) - 1);
    }

    HashMap() {
        size = 0;
    }

    // returns slot for key k (inserts if empty)
    Node &find(const K& k) {
        size_t h = hash(k);
        while (nodes[h].state == State::used && nodes[h].key != k) {
            h = (h + 1) & ((1 << D) - 1);
        }
        return nodes[h];
    }

    // const version of find
    const Node &find(const K& k) const {
        size_t h = hash(k);
        while (nodes[h].state == State::used && nodes[h].key != k) {
            h = (h + 1) & ((1 << D) - 1);
        }
        return nodes[h];
    }

    // access value by key (inserts new element if needed)
    V& operator[](const K& k) {
        Node &node = find(k);

        size += node.state == State::free;
        node.state = State::used;
        node.key = k;

        return node.value;
    }

    // returns true if key k exists in the map
    bool count(const K& k) const {
        const Node &node = find(k);

        return node.state == State::used;
    }
};

int main() {
    HashMap<long long, long long, 21> h;

    unordered_map<long long, long long> h2;
    mt19937_64 gen;

    const int W = 1000000;
    vector <long long> keys(W);
    for (auto &k : keys) k = gen();
    vector <long long> values(W);
    for (auto &v : values) v = gen();

    auto start = clock() / 1.0 / CLOCKS_PER_SEC;
    for(int i = 0; i < keys.size(); ++i) {
        h[keys[i]] = values[i];
    }
    auto end = clock() / 1.0 / CLOCKS_PER_SEC;
    cerr << "my hash write: " << (end - start) << " sec" << endl;


    start = clock() / 1.0 / CLOCKS_PER_SEC;
    for(int i = 0; i < keys.size(); ++i) {
        h2[keys[i]] = values[i];
    }
    end = clock() / 1.0 / CLOCKS_PER_SEC;
    cerr << "unordered hash write: " << (end - start) << " sec" << endl;


    for (long long k : keys) {
        assert(h[k] == h2[k]);
    }
    const int R = 10000000;
    start = clock() / 1.0 / CLOCKS_PER_SEC;

    int cnt = 0;
    for(int _ = 0; _ < R; ++_) {
        long long k = gen();
        cnt += h.count(k);
    }
    end = clock() / 1.0 / CLOCKS_PER_SEC;
    cerr << "my hash read: " << (end - start) << " sec" << endl;


    start = clock() / 1.0 / CLOCKS_PER_SEC;
    cnt = 0;
    for(int _ = 0; _ < R; ++_) {
        long long k = gen();
        cnt -= h2.count(k);
    }
    end = clock() / 1.0 / CLOCKS_PER_SEC;
    cerr << "unordered hash read: " << (end - start) << " sec" << endl;

    assert(cnt == 0);
}
