#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#define INF 0x77777777
using namespace std;

int n, m, a[101][101], vis[101][101], mincost[101][101];

string path[101][101];

int input(){
    if (scanf("%d%d", &m, &n) == EOF) {
        return 0;
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
    return 1;
}

void dp(int i, int j) {
    vis[i][j] = 1;
    if (j == 1) {
        mincost[i][j] = a[i][j];
        path[i][j] = i - 1 + '0';
        return;
    }
    for (int delta = -1; delta <= 1; ++delta) {
        int nowi = i + delta, nowj = j - 1;
        nowi = (nowi + m - 1) % m + 1;
        //printf("%d\n", nowi);
        if (!vis[nowi][nowj]) {
            dp(nowi, nowj);
        }
        string new_path = path[nowi][nowj];
        new_path += i - 1 + '0';
        if (mincost[i][j] == -1 || mincost[nowi][nowj] < mincost[i][j] || mincost[nowi][nowj] == mincost[i][j] && new_path < path[i][j]) {
            mincost[i][j] = mincost[nowi][nowj];
            path[i][j] = new_path;
        }
    }
    mincost[i][j] += a[i][j];
}

void calc(){
    memset(vis, 0, sizeof(vis));
    memset(mincost, 0xff, sizeof(mincost));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            path[i][j] = "";
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (!vis[i][n]) {
            dp(i, n);
        }
    }
}

void print() {
    int final_cost = -1;
    string final_path;
    for (int i = 1; i <= m; ++i) {
        if (final_cost == -1 || mincost[i][n] < final_cost || mincost[i][n] == final_cost && path[i][n] < final_path) {
            final_cost = mincost[i][n];
            final_path = path[i][n];
        }
    }
    for (int i = 0; i < final_path.length(); ++i) {
        printf("%d", final_path[i] - '0' + 1);
        printf("%c", i < final_path.length() - 1 ? ' ' : '\n');
    }
    printf("%d\n", final_cost);
}

int main() {
    while(input()) {
        calc();
        print();
    }
    return 0;
}
