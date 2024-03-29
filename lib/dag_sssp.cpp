#include <iostream>
#include <stdio.h>
#include <string.h>
#define MAXN 100

int n, s, map[MAXN+1][MAXN+1], vis[MAXN+1], dis[MAXN+1];

int topo_list[MAXN+1], cnt_topo_list = 0;

void topo_dfs (int node) {
    vis[node] = 1;
    for (int i = 1; i <= n; ++i) {
        if (map[node][i] && !vis[i]) {
            topo_dfs(i);
        }
    }
    topo_list[++cnt_topo_list] = node;
}

void topo_sort (void) {
    memset(topo_list, 0, sizeof(topo_list));
    cnt_topo_list = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            topo_dfs(i);
        }
    }
}

void sssp_dag (void) {
    topo_sort();
    memset(dis, 0xff, sizeof(dis));
    dis[s] = 0;
    for (int i = cnt_topo_list; i >= 1; --i) {
        int node = topo_list[i];
        for (int j = 1; j <= n; ++j) {
            if (map[node][j]) {
                if (dis[node] >= 0) {
                    if (dis[node] + map[node][j] > dis[j]) {
                        dis[j] = dis[node] + map[node][j];
                    }
                }
            }
        }
    }
}
