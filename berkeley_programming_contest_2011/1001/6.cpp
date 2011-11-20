#include"contest.h"
#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int cnt[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
long long f[100][100][2], ans[100];
int vis[100][100][2];

long long dp(int i, int j, int is_first) { // i matches representing j digits
    if (vis[i][j][is_first]) {
        return f[i][j][is_first];
    }
    vis[i][j][is_first] = 1;
    if (j == 0) {
        return f[i][j][is_first] = 1;
    } else if (i == 0 && j != 0) {
        return f[i][j][is_first] = 0;
    } else if (j == 1) {
        for (int k = 0; k <= 9; ++k) {
            if (cnt[k] <= i) {
                ++f[i][j][is_first];
            }
        }
        return f[i][j][is_first];
    } else {
        if (is_first) {
            for (int k = 1; k <= 9; ++k) {
                if (cnt[k] <= i) {
                    f[i][j][is_first] += dp(i - cnt[k], j - 1, 0);
                }
            }
        } else {
            for (int k = 0; k <= 9; ++k) {
                if (cnt[k] <= i) {
                    f[i][j][is_first] += dp(i - cnt[k], j - 1, 0);
                }
            }
        }
        return f[i][j][is_first];
    }
}
int main() {
    int n;
    for (int i = 0; i <= 80; ++i) {
        for (int j = 1; j <= i / 2; ++j) {
            if(!vis[i][j][1]) {
                dp(i, j, 1);
            }
            ans[i] += f[i][j][1];
        }
    }
    while (scanf("%d", &n) != EOF) {
        printf("%lld\n", ans[n]);
    }
    exit(0);
}
