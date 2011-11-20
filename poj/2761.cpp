#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

struct sbt {
    int l, r, s, w;
} t[200001];

struct Interval {
    int x, y, k, pos;
} interval[100001];

int ans[100001], root, tot, value[200001];

void rrot(int &k) {
    int p = t[k].l;
    t[k].l = t[p].r;
    t[p].r = k;
    t[p].s = t[k].s;
    t[k].s = t[t[k].l].s + t[t[k].r].s + 1;
    k = p;
}

void lrot(int &k) {
    int p = t[k].r;
    t[k].r = t[p].l;
    t[p].l = k;
    t[p].s = t[k].s;
    t[k].s = t[t[k].l].s + t[t[k].r].s + 1;
    k = p;
}

void maintain(int &k, int flag) {
    if (flag) {
        if (t[t[t[k].l].l].s > t[t[k].r].s) {
            rrot(k);
        } else if (t[t[t[k].l].r].s > t[t[k].r].s) {
            lrot(t[k].l);
            rrot(k);
        } else {
            return;
        }
    } else {
        if (t[t[t[k].r].r].s > t[t[k].l].s) {
            lrot(k);
        } else if (t[t[t[k].r].l].s > t[t[k].l].s) {
            rrot(t[k].r);
            lrot(k);
        } else {
            return;
        }
    }
    maintain(t[k].l, false);
    maintain(t[k].r, true);
    maintain(k, false);
    maintain(k, true);
}

void insert(int &now, int w) {
    if (!now) {
        t[++tot].l = 0;
        t[tot].r = 0;
        t[tot].s = 1;
        t[tot].w = w;
        now = tot;
        return;
    }
    if (w < t[now].w) {
        insert(t[now].l, w);
    } else {
        insert(t[now].r, w);
    }
    t[now].s = t[t[now].l].s + t[t[now].r].s + 1;
    maintain(now, w < t[now].w);
}

int del(int &now, int w) {
    --t[now].s;
    if (w == t[now].w || w < t[now].w && !t[now].l || w >= t[now].w && !t[now].r) {
        int tmp = t[now].w;
        if (!t[now].l || !t[now].r) {
            now = t[now].l + t[now].r;
        } else {
            t[now].w = del(t[now].l, w + 1);
        }
        return tmp;
    } else if (w < t[now].w) {
        return del(t[now].l, w);
    } else {
        return del(t[now].r, w);
    }
}

int select(int now, int p) {
    if (p == t[t[now].l].s + 1) {
        return now;
    } else if (p < t[t[now].l].s + 1) {
        return select(t[now].l, p);
    } else {
        return select(t[now].r, p - 1 - t[t[now].l].s);
    }
}

int cmp(const void *a, const void *b) {
    Interval *x = (Interval *)a, *y = (Interval *)b;
    return x -> x - y -> x;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &value[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &interval[i].x, &interval[i].y, &interval[i].k);
        interval[i].pos = i;
    }
    qsort(&interval[1], m, sizeof(interval[0]), cmp);
    int prev_x = interval[1].x, prev_y = interval[1].y;
    for (int i = prev_x; i <= prev_y; ++i) {
        insert(root, value[i]);
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = prev_x; j < interval[i].x; ++j) {
            del(root, value[j]);
        }
        for (int j = prev_y + 1; j <= interval[i].y; ++j) {
            insert(root, value[j]);
        }
        prev_x = interval[i].x, prev_y = interval[i].y;
        ans[interval[i].pos] = t[select(root, interval[i].k)].w;
    }
    for (int i = 1; i <= m; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
