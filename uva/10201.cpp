#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXLINE 1024
#define MAXGAS 100
#define MAXCAP 200

using namespace std;

int max(int a, int b) {
  return a < b ? b : a;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int main() {
  char input_buffer[MAXLINE];
  int gas_dis[MAXGAS+1], gas_price[MAXGAS+1];
  int f[MAXGAS+1][MAXCAP+1];
  int gas_total;
  int times;
  int ans;
  int dis_to_last, dis_to_before, city_dis;
  const int inf = 1 << 30;

  fgets(input_buffer, MAXLINE, stdin); // number of cases
  sscanf(input_buffer, "%d", &times);
  fgets(input_buffer, MAXLINE, stdin); // first empty line
  while (times--) {
    gas_total = 0;
    memset(gas_dis, 0, sizeof(gas_dis));
    memset(gas_price, 0, sizeof(gas_price));
    memset(f, 0, sizeof(f));

    fgets(input_buffer, MAXLINE, stdin); // distance
    sscanf(input_buffer, "%d", &city_dis);
    while (1) {
      if (fgets(input_buffer, MAXLINE, stdin) == NULL) {
        break;
      }
      if (input_buffer == NULL || strlen(input_buffer) <= 1) { // empty line
        break;
      }
      ++gas_total;
      sscanf(input_buffer, "%d%d", &gas_dis[gas_total], &gas_price[gas_total]);
    }
    gas_dis[0] = 0;
    for (int k = 0; k <= MAXCAP; ++k) {
      f[0][k] = inf;
    }
    f[0][100] = 0;
    for (int i = 1; i <= gas_total; ++i) {
      for (int k = 0; k <= MAXCAP; ++k) {
        f[i][k] = inf;
        dis_to_before = gas_dis[i] - gas_dis[i - 1];
        for (int j = dis_to_before; j <= min(k + dis_to_before, MAXCAP); ++j) {
          if (f[i - 1][j] < inf) {
            f[i][k] = min(f[i][k], f[i - 1][j] + gas_price[i] * (k + dis_to_before - j));
          }
        }
      }
    }
    ans = inf;
    dis_to_last = city_dis - gas_dis[gas_total];
    for (int j = dis_to_last + 100; j <= 200; ++j) {
      ans = min(ans, f[gas_total][j]);
    }
    if (ans < inf) {
      printf("%d\n", ans);
    } else {
      printf("Impossible\n");
    }
    if (times) {
      printf("\n");
    }
  }
  return 0;
}
