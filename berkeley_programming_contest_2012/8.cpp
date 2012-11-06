#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXC 64

using namespace std;
typedef long long int bigint;

bigint _comb[MAXC][MAXC];

void initcombs(void) {
  _comb[0][0] = 1;
  for (int i = 1; i <= MAXC; ++i) {
    _comb[i][0] = _comb[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      _comb[i][j] = _comb[i - 1][j] + _comb[i - 1][j - 1];
    }
  }
}

bigint comb(int n, int k) {
  return _comb[n][k];
}

bigint position(bigint n) {
  int pos = 0;
  int curone = 0;
  bigint ans = 0;
  while (n) {
    ++pos;
    if (n & 1) {
      ++curone;
      ans += comb(pos - 1, curone);
    }
    n >>= 1;
  }
  return ans;
}

int numones(bigint n) {
  int cnt = 0;
  while (n) {
    cnt += n & 1;
    n >>= 1;
  }
  return cnt;
}


int main() {
  initcombs();
  bigint n;
  while (cin >> n) {
    cout << n << " is number " << position(n) << " in the sequence of numbers with " << numones(n) << " 1-bits." << endl;
  }
  return 0;
}
