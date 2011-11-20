#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXN 1001
#define INFTY 0x77777777
using namespace std;

int p, n, start, end;

int v[MAXN][MAXN], used[MAXN], linked[MAXN], ans;

void input(){
    memset(v, 0, sizeof(v));
    memset(used, 0, sizeof(used));
    memset(linked, 0, sizeof(linked));
    scanf("%d%d", &p, &n);
    for (int i = 1, cnt; i <= p; ++i) {
        scanf("%d", &cnt);
        for (int j = 1, sid; j <= cnt; ++j) {
            scanf("%d", &sid);
            v[i][sid + p] = 1;
        }
    }
}

int can (int t) {
    int i;
    for (i = 1; i <= n + p; ++i) {
        if (!used[i] && v[t][i]) {
            used[i] = 1;
            if (!linked[i] || can(linked[i])) {
                linked[i] = t;
                return 1;
            }
        }
    }
    return 0;
}

void hungarian() {
    ans = 0;
    for (int i = 1; i <= p; ++i) {
        memset(used, 0, sizeof(used));
        ans += can(i);
    }
}

void calc() {
    hungarian();
    if (ans == p) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main(){
    int cases;
    scanf("%d", &cases);
    for (int i = 1; i <= cases; ++i) {
        input();
        calc();
    }
    return 0;
}
