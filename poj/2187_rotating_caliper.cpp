#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits.h>

#define MAXN 100000

using namespace std;

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y) {
    x = _x;
    y = _y;
  }

  Point operator -(const Point &b) const {
    return Point(x - b.x, y - b.y);
  }

  int operator *(const Point &b) const {
    return x * b.y - y * b.x;
  }

  int operator &(const Point &b) const {
    return x * b.x + y * b.y;
  }
};

int sqrdis(Point a, Point b) {
  return (a - b) & (a - b);
}

void convex_hull(Point p[], int n, Point res[], int &resn) {
  resn = 0;
  int top = 0;
  sort(p, p+n, ch_cmp);
  for (int i = 0; i < n;) {
    if (resn < 2 ||
      (res[resn - 1] - res[resn - 2]) * (p[i] - res[resn - 1]) > 0) {
      res[resn++] = p[i++];
    } else {
      --resn;
    }
  }
  top = resn - 1;
  for (int i = n - 2; i >= 0;) {
    if (resn < top + 2 ||
      (res[resn - 1] - res[resn - 2]) * (p[i] - res[resn - 1]) > 0) {
      res[resn++] = p[i--];
    } else {
      --resn;
    }
  }
  --resn;
}

int rotating_caliper(Point p[], int n) {
  Point v;
  int cur = 1;
  int max_sqrdis = INT_MIN;
  for (int i = 0; i < n; ++i) {
    v = p[i] - p[(i + 1) % n];
    while (v * (p[(cur + 1) % n] - p[cur]) < 0) {
      cur = (cur + 1) % n;
    }
    if (sqrdis(p[cur], p[i]) > max_sqrdis) {
      max_sqrdis = sqrdis(p[cur], p[i]);
    }
    if (sqrdis(p[cur], p[i + 1]) > max_sqrdis) {
      max_sqrdis = sqrdis(p[cur], p[i + 1]);
    }
  }
  return max_sqrdis;
}

Point p[MAXN+1], res[MAXN+1];
int main() {
  int n, resn;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> p[i].x >> p[i].y;
  }
  convex_hull(p, n, res, resn);
  cout << rotating_caliper(res, resn) << endl;
  return 0;
}
