#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <iostream>

#define MAXN 100

using namespace std;

typedef double coord_t;
typedef double coord2_t;

class Point {
public:
    coord_t x, y;
    Point () {
        x = 0;
        y = 0;
    }
    Point (coord_t tx, coord_t ty) {
        x = tx;
        y = ty;
    }
    bool operator <(const Point &p) const {
        return x < p.x || x == p.x && y < p.y;
    }
};

inline coord2_t cross(const Point &O, const Point &A, const Point &B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> P) {
    int n = P.size(), k = 0;
    vector<Point> H(2 * n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) { // The point with index n - 1 is already in H
        while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k - 1);
    return H;
}
