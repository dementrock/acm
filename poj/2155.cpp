#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXN 1010
using namespace std;

int n, bit[MAXN + 1][MAXN + 1];

inline int lowbit (int x) {
    return x & -x;
}

int getsum (int x, int y) {
    int res = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) {
        for (int j = y; j >= 1; j -= lowbit(j)) {
            res += bit[i][j];
        }
    }
    return res;
}

void add(int x, int y, int amount) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= n; j += lowbit(j)) {
            bit[i][j] += amount;
        }
    }
}

void init() {
    memset(bit, 0, sizeof(bit));
    int t;
    char c;
    scanf("%d %d\n", &n, &t);
    for (int i = 1, x1, y1, x2, y2, x, y; i <= t; ++i) {
        scanf("%c", &c);
        if (c == 'C') {
            scanf(" %d %d %d %d\n", &x1, &y1, &x2, &y2);
            add(x2 + 1, y2 + 1, 1);
            add(x1, y1, 1);
            add(x1, y2 + 1, 1);
            add(x2 + 1, y1, 1);
        }
        else {
            scanf(" %d %d\n", &x, &y);
            printf("%d\n", getsum(x, y) % 2);
        }
    }
}

int main() {
    int cases;
    scanf("%d\n", &cases);
    for (int i = 1; i <= cases; ++i) {
        init();
        if (i < cases) {
            printf("\n");
        }
    }
    return 0;
}
