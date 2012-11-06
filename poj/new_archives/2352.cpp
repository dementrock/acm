#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int bit[32001], cnt[32001];

inline int lowbit (int x) {
    return x & -x;
}

int getsum (int x) {
    int res = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) {
        res += bit[i];
    }
    return res;
}

void add(int x, int amount) {
    for (int i = x; i <= 32001; i += lowbit(i)) {
        bit[i] += amount;
    }
}

int main() {
    int n, x, y;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &x, &y);
        ++x, ++y;
        ++cnt[getsum(x)];
        add(x, 1);
    }
    for (int i = 0; i < n; ++i) {
        printf("%d\n", cnt[i]);
    }
    return 0;
}
