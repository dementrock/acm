#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXN 1001

using namespace std;

map<string, int> indexmap;  

int oo = 99999999;
int edge[MAXN][MAXN], n;

int find_index(string city_name) {
  if (!indexmap[city_name]) {
    return indexmap[city_name] = ++n;
  }
  return indexmap[city_name];
}

int maxfloyd(void) {
  int maxdis = 0;
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i)  if (i != k && edge[i][k] > 0) {
      for (int j = 1; j <= n; ++j) if (j != i && j != k && edge[k][j] > 0) {
        if (edge[i][j] < 0 || edge[i][k] + edge[k][j] < edge[i][j]) {
          edge[i][j] = edge[j][i] = edge[i][k] + edge[k][j];
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (edge[i][j] > 0 ) {
        maxdis = max(maxdis, edge[i][j]);
      }
    }
  }
  return maxdis;
}

int add_edge(int i, int j, int dis) {
  edge[i][j] = dis;
}

void init(void) {
  memset(edge, 0xff, sizeof(edge));
  n = 0;
  indexmap.clear();
}


int main() {
  string s, t;
  int cntset = 0;
  int N, dis;
  while((cin >> N) && N) {
    init();
    for (int i = 0; i < N; ++i) {
      cin >> s >> t >> dis;
      add_edge(find_index(s), find_index(t), dis);
      add_edge(find_index(t), find_index(s), dis);
    }
    cout << "Set #" << ++cntset << ": " << maxfloyd() << " miles" << endl;
  }
  return 0;
}
