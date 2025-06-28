#include <bits/stdc++.h>

const long double eps = 1e-9;

struct Point {
    long double x, y;
    Point(long double  xx = 0, long double  yy = 0) : x(xx), y(yy) {}
    Point operator-(const Point &r) const {
        return Point(x - r.x, y - r.y);
    }
    Point operator+(const Point &r) const {
        return Point(x + r.x, y + r.y);
    }
    Point operator*(const long double &r) const {
        return Point(x * r, y * r);
    }

    friend long double  dot(const Point &l, const Point &r) {
        return l.x * r.x + l.y * r.y;
    }
    friend long double  cross(const Point &l, const Point &r) {
        return l.x * r.y - l.y * r.x;
    }
    long double dist(const Point &r) const {
        return sqrt((x - r.x) * (x - r.x) + (y - r.y) * (y - r.y));
    }
    friend ostream & operator<<(ostream & os, const Point &r) {
        return os << "{" << r.x << ", " << r.y << "}";
    }
    bool operator<(const Point &r) const {
        return x < r.x || (abs(x - r.x) < eps && y + eps < r.y);
    }
    bool operator==(const Point &r) const {
        return abs(x - r.x) < eps && abs(y - r.y) < eps;
    }
};


void makeConvex(vector <Point> &points) {
    if (points.size() < 3) {
        return;
    }
    iter_swap(points.begin(), min_element(points.begin(), points.end()));
    auto cmp = [&](const Point &l, const Point &r) {
        long double cr = cross(l - points.front(), r - points.front());
        if (fabs(cr) > eps) {
            return cr > 0;
        }
        return dot(l - points.front(), l - points.front()) < dot(r - points.front(), r - points.front());
    };
    sort(points.begin() + 1, points.end(), cmp);

    vector <Point> hull;

    for (const Point & point : points) {
        while (hull.size() > 1 && cross(hull[hull.size() - 1] - hull[hull.size() - 2], point - hull[hull.size() - 2]) < eps) {
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
