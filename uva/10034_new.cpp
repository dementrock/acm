#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
using namespace std;

struct edge{
    int x, y;
    double l;
} e[20001];

int cnt_e = 0, n, father[101];

double x[101], y[101], ans; 

void init(){
    cnt_e = 0;
    memset(e, 0, sizeof(e));
    ans = 0;
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    memset(father, 0, sizeof(father));
}

void input(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        scanf("%lf%lf", &x[i], &y[i]);
    }
}

double calcdis(double x1, double y1, double x2, double y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void add_edge(int x, int y, double l){
    e[++cnt_e].x = x;
    e[cnt_e].y = y;
    e[cnt_e].l = l;
}

inline double abs(double x){
    return x >= 0 ? x : -x;
}

inline int zero(double x){
    return abs(x) < 1e-10;
}

inline int same(double x, double y){
    return zero(x-y);
}

int cmp(const void *x, const void *y){
    edge *a = (edge *) x;
    edge *b = (edge *) y;
    if (same(a -> l, b -> l)) {
        return 0;
    }
    else if (a -> l < b -> l) {
        return -1;
    }
    else {
        return 1;
    }
}

int getfather(int x){
    if (father[x] == x) {
        return x;
    }
    return father[x] = getfather(father[x]);
}

void merge(int x, int y, double l){
    if (getfather(x) != getfather(y)) {
        ans += l;
        father[getfather(x)] = getfather(y);
    }
}

void kruskal(){
    for (int i = 1; i <= cnt_e; ++i){
        merge(e[i].x, e[i].y, e[i].l);
    }
}

void calc(){
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
    }

    for (int i = 1; i <= n; ++i){
        for (int j = i + 1; j <= n; ++j){
            add_edge(i, j, calcdis(x[i], y[i], x[j], y[j]));
        }
    }
    qsort(e + 1, cnt_e, sizeof(e[0]), cmp);
    kruskal();
}

void print(){
    printf("%.2lf\n", ans);
}

int main(){
    int cases;
    scanf("%d", &cases);
    for (int i = 1; i <= cases; ++i){
        init();
        input();
        calc();
        print();
    }
    return 0;
}
