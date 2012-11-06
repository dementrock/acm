#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXN 2001 
#define MAXM 4000001
#define INFTY 0x77777777
using namespace std;

struct edge{
    int x, y;
    int l;
} e[MAXM];

int cnt_e = 0, n, father[MAXN], ans = 0;

char str[MAXN][10];

void add_edge(int x, int y, int l){
    e[++cnt_e].x = x;
    e[cnt_e].y = y;
    e[cnt_e].l = l;
}

int getfather(int x){
    if (father[x] == x) {
        return x;
    }
    return father[x] = getfather(father[x]);
}

void merge(int x, int y, int l){
    int a = getfather(x), b = getfather(y);
    if (a != b) {
        ans += l;
        father[a] = b;
    }
}

int cmp(const void *x, const void *y){
    edge *a = (edge *) x;
    edge *b = (edge *) y;
    return a -> l - b -> l;
}


void kruskal(){
    qsort(e + 1, cnt_e, sizeof(e[0]), cmp);
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
    }
    for (int i = 1; i <= cnt_e; ++i){
        merge(e[i].x, e[i].y, e[i].l);
    }
}

int input() {
    scanf("%d\n", &n);
    if (!n) {
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%s\n", str[i]);
    }
    return 1;
}

int calcdis(int i, int j) {
    int res = 0;
    for (int k = 0; k < 7; ++k) {
        if (str[i][k] != str[j][k]) {
            ++res;
        }
    }
    return res;
}

void calc() {
    ans = 0;
    cnt_e = 0;
    memset(e, 0, sizeof(e));
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            add_edge(i, j, calcdis(i, j));
        }
    }
    kruskal();
    printf("The highest possible quality is 1/%d.\n", ans);
}

int main(){
    while(input()) {
        calc();
    }
    return 0;
}
