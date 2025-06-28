#include <bits/stdc++.h>

struct Automaton {
    using moves_t = vector <pair <int, int> >;
    vector <moves_t> go;
    int source;
    vector <int> isTerminal;

    void ensureIndex(int index) {
        if (index >= go.size()) {
            go.resize(index + 1);
            isTerminal.resize(index + 1);
        }

    }

    Automaton(int source): source(source) {
        ensureIndex(source);
    }

    void setTerminal(int index) {
        ensureIndex(index);
        isTerminal[index] = 1;
    }

    void addEdge(int from, int to, int c) {
        ensureIndex(from);
        ensureIndex(to);
        go[from].emplace_back(c, to);
    }

    void normalize() {
        for (auto &x : go) {
            sort(all(x));
        }
    }

    moves_t merge(const vector <int> &vertices) const {
        vector <moves_t::const_iterator> ids(vertices.size());
        for (int i = 0; i < vertices.size(); ++i) {
            ids[i] = go[vertices[i]].begin();
        }

        moves_t result;
        while (true) {
            bool found = false;
            moves_t::const_iterator *best;
            for (int i = 0; i < vertices.size(); ++i) {
                if (ids[i] == go[vertices[i]].end()) continue;

                if (!found || *ids[i] < **best) {
                    best = &ids[i];
                }

                found = true;
            }

            if (!found) {
                break;
            }

            result.push_back(**best);
            best->operator++();
        }

        return result;
    }

    Automaton DFA() const {
        queue <vector <int> > q;
        map <vector <int>, int> index;

        auto getIndex = [&index](const vector <int> &vertices, int &result) {
            auto it = index.find(vertices);
            if (it != index.end()) {
                result = it->second;
                return true;
            }
            int id = index.size();
            index[vertices] = id;
            result = id;

            return false;
        };

        auto init = vector <int>(1, source);
        int initIndex;
        getIndex(init, initIndex);
        Automaton result(initIndex);
        q.push(init);

        vector <int> used(go.size());

        while (!q.empty()) {
            auto v = move(q.front());
            q.pop();

            int vIndex;
            getIndex(v, vIndex);

            auto merged = merge(v);
            for (int i = 0; i < merged.size();) {
                vector <int> to;
                int j = i;
                while (j < merged.size() && merged[i].first == merged[j].first) {
                    if (!used[merged[j].second]) {
                        to.push_back(merged[j].second);
                        used[merged[j].second] = 1;
                    }
                    ++j;
                }

                int toIndex;
                if (!getIndex(to, toIndex)) {
                    q.push(to);
                }

                result.addEdge(vIndex, toIndex, merged[i].first);

                for (int id : to) {
                    used[id] = 0;
                }

                i = j;
            }
        }

        for (const auto &kv: index) {
            bool isT = false;
            for (int i: kv.first) {
                isT |= isTerminal[i];
            }

            if (isT) {
                result.setTerminal(kv.second);
            }
        }

        return result;
    }
};
