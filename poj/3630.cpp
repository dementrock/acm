#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int n;

char phone[20001][11] = {};

int cmp(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

void init() {
    scanf("%d", &n);
    memset(phone, 0, sizeof(phone));
    for (int i = 0; i < n; ++i) {
        scanf("%s", phone[i]);
    }
}

int isprefix(char a[], char b[]) {
    if (strlen(a) > strlen(b)) {
        return 0;
    }
    for (int i = 0; i < strlen(a); ++i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int work() {
    qsort(phone, n, sizeof(phone[0]), cmp);
    for (int j = 0; j < n - 1; ++j) {
        if (isprefix(phone[j], phone[j + 1])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int t;
    scanf ("%d", &t);
    for (int i = 1; i <= t; ++i) {
        init();
        printf("%s\n", work() ? "YES" : "NO");
    }
    return 0;
}
