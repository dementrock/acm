#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXM 100001
#define MAXN 1001
#define INFTY 0x77777777
using namespace std;

int prev_n, n, m, k, start, end;

struct Edge
{
	int v;
	int w;
	Edge *next, *reverse;
} *edge[MAXM],mempool[MAXM];

int memnum;

int v[MAXN][MAXN], layer[MAXN], minf = INFTY, counter[MAXN], found = 0, ans = 0;

string receptacle[MAXN], plug[MAXN], from[MAXN], to[MAXN], device[MAXN];

void add(int u, int v, int w)
{
    Edge *e1 = &mempool[++memnum], *e2 = &mempool[++memnum];
    e1 -> v = v, e2 -> v = u;
    e1 -> w = w, e2 -> w = 0;
    e1 -> next = edge[u], e2 -> next = edge[v];
    e1 -> reverse = e2, e2 -> reverse = e1;
    edge[u] = e1, edge[v] = e2;
}

int r_find(string s) {
    for (int i = 1; i <= n; ++i) {
        if (s == receptacle[i]) {
            return i + m;
        }
    }
    receptacle[++n] = s;
    return n;
}

void input(){
    cin >> n;
    prev_n = n;
    for (int i = 1; i <= n; ++i) {
        cin >> receptacle[i];
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> device[i] >> plug[i];
        r_find(plug[i]);
    }
    cin >> k;
    for(int i = 1; i <= k; ++i) {
        cin >> from[i] >> to[i];
        r_find(from[i]), r_find(to[i]);
    }
}

void aug(int now) {
    int i, cache_minf = minf, minl = end;
    if (now == end) {
        found = 1;
        ans += minf;
        return;
    }
    Edge *e;
    for (e = edge[now]; e != NULL; e = e -> next) {
        if (e -> w > 0) {
            if (layer[now] == layer[e -> v] + 1) {
                minf = min(minf, e -> w);
                aug(e -> v);
                if (layer[start] > end) {
                    return;
                }
                if (found) {
                    break;
                }
                minf = cache_minf;
            }
            if (layer[e -> v] < minl) {
                minl = layer[e -> v];
            }
        }
    }
    if (!found) {
        if (--counter[layer[now]] == 0) {
            layer[start] = end + 1;
        }
        ++counter[layer[now] = minl + 1];
    } else {
        e -> w -= minf;
        e -> reverse -> w += minf;
    }
}

void sap() {
    memset(layer, 0, sizeof(layer));
    memset(counter, 0, sizeof(counter));
    counter[0] = end + 1;
    ans = 0;
    while (layer[start] <= end) {
        minf = INFTY;
        found = 0;
        aug(start);
    }
}

void calc() {
    start = 0, end = m + n + 1;
    for (int i = 1; i <= m; ++i) {
        add(start, i, 1);
        add(i, r_find(plug[i]), 1);
    }
    for (int i = 1; i <= prev_n; ++i) {
        add(r_find(receptacle[i]), end, 1);
    }
    for (int i = 1; i <= k; ++i) {
        add(r_find(from[i]), r_find(to[i]), INFTY);
    }
    sap();
    printf("%d\n", m - ans);
}

int main(){
    input();
    calc();
    return 0;
}
