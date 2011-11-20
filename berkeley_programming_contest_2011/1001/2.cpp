#include"contest.h"
#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int cnt[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
long long f[11][500][5000];
int vis[11][500][5000];

long long dp(int base, int i, int j) { // first i digits representing sum j
    //printf("%d %d %d\n",base,i,j);
    if (vis[base][i][j]) {
        return f[base][i][j];
    }
    vis[base][i][j] = 1;
    if (i == 0 && j == 0) {
        return f[base][i][j] = 1;
    } else if (i == 0) {
        return f[base][i][j] = 0;
    } else if (j == 0) {
        return f[base][i][j] = 1;
        //printf("haha");
    } else {
        for (int k = 0; k < base; ++k) {
            if (j >= k) {
                f[base][i][j] += dp(base, i - 1, j - k);
            }
        }
        return f[base][i][j];
    }
}
int main() {
    int n, base;
    while (scanf("%d%d", &n, &base) != EOF) {
        long long ans = 0;
        for (int i = 0; i <= n / 2 * (base - 1); ++i) {
            ans += dp(base, n / 2, i) * dp(base, n / 2, i);
        }
        printf("There are %lld %d-digit base %d lucky numbers.\n", ans, n, base);
    }
    exit(0);
}
