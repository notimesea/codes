#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    Point(long long xx = 0, long long yy = 0) : x(xx), y(yy) {}
    Point operator-(const Point &r) const {
        return Point(x - r.x, y - r.y);
    }
    Point operator+(const Point &r) const {
        return Point(x + r.x, y + r.y);
    }
    Point operator*(const long long &r) const {
        return Point(x * r, y * r);
    }

    friend long long dot(const Point &l, const Point &r) {
        return l.x * r.x + l.y * r.y;
    }
    friend long long cross(const Point &l, const Point &r) {
        return l.x * r.y - l.y * r.x;
    }
    long long distance(const Point &r) const {
        return (x - r.x) * (x - r.x) + (y - r.y) * (y - r.y);
    }
    friend ostream & operator<<(ostream & os, const Point &r) {
        return os << "{" << r.x << ", " << r.y << "}";
    }
    bool operator<(const Point &r) const {
        return x < r.x || (x == r.x && y < r.y);
    }
    bool operator==(const Point &r) const {
        return x == r.x && y == r.y;
    }
};

void makeConvex(vector <Point> &points) {
    if (points.size() < 3) {
        return;
    }
    iter_swap(points.begin(), min_element(points.begin(), points.end()));
    auto cmp = [&](const Point &l, const Point &r) {
        long long cr = cross(l - points.front(), r - points.front());
        if (cr != 0) {
            return cr > 0;
        }
        return dot(l - points.front(), l - points.front()) < dot(r - points.front(), r - points.front());
    };
    sort(points.begin() + 1, points.end(), cmp);

    vector <Point> hull;

    for (const Point & point : points) {
        while (hull.size() > 1 && cross(hull[hull.size() - 1] - hull[hull.size() - 2], point - hull[hull.size() - 2]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(point);
    }
    points.swap(hull);
}

void makeUnique(vector <Point> &points) {
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
}
