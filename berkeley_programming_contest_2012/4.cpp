#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXL 2000

using namespace std;

int f[MAXL][MAXL];

int oo = 99999999;

int solve(string a, string b) {
  memset(f, 0, sizeof(f));
  f[0][0] = 0;
  for (int i = 1; i <= a.length(); ++i) {
    f[i][0] = i;
  }
  for (int i = 1; i <= b.length(); ++i) {
    f[0][i] = i;
  }
  for (int i = 1; i <= a.length(); ++i) {
    for (int j = 1; j <= b.length(); ++j) {
      f[i][j] = oo;
      if (a[i - 1] == b[j - 1]) {
        f[i][j] = f[i - 1][j - 1];
      }
      f[i][j] = min(f[i][j], f[i - 1][j] + 1);
      f[i][j] = min(f[i][j], f[i][j - 1] + 1);
    }
  }
  return f[a.length()][b.length()];
}

int main() {
  string sa, sb;
  while (getline(cin, sa) && getline(cin, sb)) {
    cout << solve(sa, sb) << endl;
  }
  return 0;
}

