#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXS 30
#define MAXN 10

using namespace std;

struct slot{
  int x, y;
  int pose; // 0: left to right; 1: top to down
  int nconstraints;
} slots[MAXS];

int W, H;
int cntslots;
int colplus[MAXN], colminus[MAXN], rowplus[MAXN], rowminus[MAXN];
int colplussum[MAXN], colminussum[MAXN], rowplussum[MAXN], rowminussum[MAXN];
int map[MAXN][MAXN];

void place(int x, int y, int type) { // type  0: x, 1: +, 2: -
  if (type == 0) {
    if (map[x][y] == 1) {
      --colplussum[y];
      --rowplussum[x];
    } else if (map[x][y] == 2) {
      --colminussum[y];
      --rowminussum[x];
    }
    map[x][y] = 0;
  } else if (type == 1) {
    ++colplussum[y];
    ++rowplussum[x];
    map[x][y] = 1;
  } else {
    ++colminussum[y];
    ++rowminussum[x];
    map[x][y] = 2;
  }
}

bool sum_satisfiable(int x, int y) {
  return (colplus[y] < 0 || colplus[y] >= colplussum[y]) && 
         (colminus[y] < 0 || colminus[y] >= colminussum[y]) &&
         (rowplus[x] < 0 || rowplus[x] >= rowplussum[x]) &&
         (rowminus[x] < 0 || rowminus[x] >= rowminussum[x]);
}

bool orthogonal_satisfied(int x, int y) {
  return !map[x][y] || (
    map[x][y] != map[x-1][y] &&
    map[x][y] != map[x][y-1] &&
    map[x][y] != map[x+1][y] &&
    map[x][y] != map[x][y+1]
  );
}

bool constraints_satisfiable(int x, int y) {
  return sum_satisfiable(x, y) && orthogonal_satisfied(x, y);
}

bool constraints_satisfied() {
  for (int i = 1; i <= W; ++i) {
    if (colplus[i] > 0 && colplus[i] != colplussum[i] || colminus[i] > 0 && colminus[i] != colminussum[i]) {
      return false;
    }
  }
  for (int i = 1; i <= H; ++i) {
    if (rowplus[i] > 0 && rowplus[i] != rowplussum[i] || rowminus[i] > 0 && rowminus[i] != rowminussum[i]) {
      return false;
    }
  }
  return true;
}

bool dfs(int depth) {
  if (constraints_satisfied()) {
    return true;
  } else if (depth > cntslots) {
    return false;
  }
  int x1 = slots[depth].x, y1 = slots[depth].y, x2, y2;
  if (slots[depth].pose == 0) { // left to right
    x2 = x1;
    y2 = y1 + 1;
  } else { // top to down
    x2 = x1 + 1;
    y2 = y1;
  }


  //printf("%d %d; %d %d\n", x1, y1, x2, y2);
  place(x1, y1, 1);
  place(x2, y2, 2);
  if (constraints_satisfiable(x1, y1) && constraints_satisfiable(x2, y2)) {
    if (dfs(depth + 1)) {
      return true;
    }
  }
  place(x1, y1, 0);
  place(x2, y2, 0);

  
  place(x1, y1, 2);
  place(x2, y2, 1);

  if (constraints_satisfiable(x1, y1) && constraints_satisfiable(x2, y2)) {
    if (dfs(depth + 1)) {
      return true;
    }
  }
  place(x1, y1, 0);
  place(x2, y2, 0);

  if (dfs(depth + 1)) {
    return true;
  }

  return false;

}

void search_solution(void) {
  dfs(1);
}

int main() {
  string s;
  int times = 0;
  while (cin >> W >> H && W && H) {
    cntslots = 0;
    memset(colplussum, 0, sizeof(colplussum));
    memset(colminussum, 0, sizeof(colminussum));
    memset(rowplussum, 0, sizeof(rowplussum));
    memset(rowminussum, 0, sizeof(rowminussum));
    memset(map, 0, sizeof(map));
    for (int i = 1; i <= W; ++i) {
      cin >> colplus[i];
    }
    for (int i = 1; i <= W; ++i) {
      cin >> colminus[i];
    }
    for (int i = 1; i <= H; ++i) {
      cin >> rowplus[i];
    }
    for (int i = 1; i <= H; ++i) {
      cin >> rowminus[i];
    }
    for (int i = 1; i <= H; ++i) {
      cin >> s;
      for (int j = 0; j < s.length(); ++j) {
        if (s[j] == 'T' || s[j] == 'L') {
          ++cntslots;
          slots[cntslots].x = i;
          slots[cntslots].y = j + 1;
          slots[cntslots].pose = s[j] == 'T';
          //cout << "slot: " << slots[cntslots].x << " " << slots[cntslots].y << endl;
        }
      }
    }
    //cout << cntslots << endl;
    search_solution();
    if (times) {
      cout << endl;
    }
    cout << "Set " << ++times << ":" << endl;
    for (int i = 1; i <= H; ++i) {
      cout << "   ";
      for (int j = 1; j <= W; ++j) {
        if (map[i][j] == 1) {
          cout << "+";
        } else if (map[i][j] == 2) {
          cout << "-";
        } else {
          cout << "x";
        }
      }
      cout << endl;
    }
  }
  return 0;
}
