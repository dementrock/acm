#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 10000

using namespace std;

struct coord {
  int x, y;
} loc[2 * MAXN];

int direction[][2] = {
  {0, 0},
  {0, -1}, // down
  {-1, 0}, // leftdown
  {-1, 1}, // leftup
  {0, 1}, // up
  {1, 0}, // rightup
  {1, -1}, // rightdown
};

void record(int num, coord prevloc, int d) {
  loc[num].x = prevloc.x + direction[d][0];
  loc[num].y = prevloc.y + direction[d][1];
}

void init(void) {
  loc[1].x = loc[1].y = 0;
  int num = 1;
  for (int round = 0; ; ++round) {
    record(num + 1, loc[num], 1);
    ++num;
    for (int i = 0; i < round; ++i) {
      record(num + 1, loc[num], 2); 
      ++num;
    }
    for (int i = 0; i < round + 1; ++i) {
      record(num + 1, loc[num], 3); 
      ++num;
    }
    for (int i = 0; i < round + 1; ++i) {
      record(num + 1, loc[num], 4); 
      ++num;
    }
    for (int i = 0; i < round + 1; ++i) {
      record(num + 1, loc[num], 5); 
      ++num;
    }
    for (int i = 0; i < round + 1; ++i) {
      record(num + 1, loc[num], 6); 
      ++num;
    }
    for (int i = 0; i < round + 1; ++i) {
      record(num + 1, loc[num], 1); 
      ++num;
    }
    if (num >= MAXN) {
      break;
    }
  }
}

int dis(int a, int b) {
  coord ca = loc[a], cb = loc[b];
  if (cb.x >= ca.x && cb.y <= ca.y || cb.x <= ca.x && cb.y >= ca.y) {
    return max(abs(ca.x - cb.x), abs(ca.y - cb.y));
  }
  return abs(ca.x - cb.x) + abs(ca.y - cb.y);
}

int main() {
  int a, b;
  init();
  while (cin >> a >> b) {
    if (!a && !b) {
      break;
    }
    cout << "The distance between cells " << a << " and " << b << " is " << dis(a, b) << "." << endl;
  }
  return 0;
}
