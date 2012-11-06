#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXM 100001
#define MAXN 1001
#define INFTY 0x77777777
using namespace std;

char w[10001], t[1000001];
int p[10001], ans;

void input() {
    scanf("%s%s", w, t);
}

void calc() {
    ans = 0;
    memset(p, 0, sizeof(p));
    p[0] = -1;
    int lenw = strlen(w), lent = strlen(t);
    for (int i = 1, j = -1; i < lenw; ++i) {
        for (; j >= 0 && w[j + 1] != w[i]; j = p[j]);
        if (w[j + 1] == w[i]) {
            ++j;
        }
        p[i] = j;
    }
    for (int i = 0, j = -1; i < lent; ++i) {
        for (; j >= 0 && w[j + 1] != t[i]; j = p[j]);
        if (w[j + 1] == t[i]) {
            ++j;
        }
        if (j == lenw - 1) {
            ++ans;
            j = p[j];
        }
    }
    printf("%d\n", ans);
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
