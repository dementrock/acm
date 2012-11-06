#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1000

int appeared[MAXN + 1], deg[MAXN + 1], map[MAXN + 1][MAXN + 1], vis[MAXN + 1], cnt_edge;

void floodfill (int now) {
    vis[now] = 1;
    for (int i = 1; i <= MAXN; ++i) {
        if (appeared[i] && !vis[i] && map[now][i]) {
            floodfill(i);
        }
    }
}

int check() {
    int root;
    int cnt_nodes = 0;
    for (int i = 1; i <= MAXN; ++i) {
        cnt_nodes += appeared[i];
    }
    if (!cnt_nodes) { // Empty tree
        return 1;
    }
    if (cnt_edge != cnt_nodes - 1) { // Edge number condition
        return 0;
    }
    for (root = 1; root <= MAXN; ++root) {
        if (appeared[root] && !deg[root]) {
            break;
        }
    }
    if (root > MAXN) { // No root
        return 0;
    }

    for (int i = 1; i <= MAXN; ++i) { // Degree condition
        if (i != root && appeared[i] && deg[i] != 1) {
            return 0;
        }
    }
    floodfill(root);
    for (int i = 1; i <= MAXN; ++i) { // Forest
        if (appeared[i] && !vis[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int ncase = 1, x, y;
    while(scanf("%d%d", &x, &y) != EOF) {
        if (x < 0 || y < 0) {
            break;
        }
        if (!x || !y) {
            if (check()) {
                printf("Case %d is a tree.\n", ncase);
            } else {
                printf("Case %d is not a tree.\n", ncase);
            }
            ++ncase;
            memset(deg, 0, sizeof(deg));
            memset(map, 0, sizeof(map));
            memset(vis, 0, sizeof(vis));
            memset(appeared, 0, sizeof(appeared));
            cnt_edge = 0;
        } else {
            map[x][y] = 1;
            ++deg[y];
            appeared[x] = appeared[y] = 1;
            ++cnt_edge;
        }
    }
    return 0;
}
