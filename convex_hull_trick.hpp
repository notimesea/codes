// Convex hull trick for monotonic lines.
#include <bits/stdc++.h>

struct Line {
    long long m, b;

    long long eval(long long x) {
        return m * x + b;
    }
};


long long comp(Line a, Line b, Line c) {
    return (b.m - a.m) * (c.b - a.b) + (b.b - a.b) * (a.m - c.m);
}

struct Hull {
    vector <Line> lines;

    void add(const Line &line) {
        if (!lines.empty()) assert(line.m > lines.back().m || (line.m == lines.back().m && line.b > /* < for minima */ lines.back().b);
        while (lines.size() >= 2 && comp(lines[lines.size() - 2], lines[lines.size() - 1], line) >= 0 /* <= 0 for minima */) {
            lines.pop_back();
        }
        lines.push_back(line);
    }

    int ptr = 0;

    long long eval(long long x) {
        while (ptr > 0 && lines[ptr].eval(x) < lines[ptr - 1].eval(x)) {
            --ptr;
        }
        while (ptr + 1 < lines.size() && lines[ptr].eval(x) < lines[ptr + 1].eval(x)) {
            ++ptr;
        }
        return lines[ptr].eval(x);
    }
};
