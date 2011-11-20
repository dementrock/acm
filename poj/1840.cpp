#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int cubic[200];
short cnt[30000000];

int hash(int x) {
    return (x + 13000000);
}

int main() {
    int ans = 0, a1, a2, a3, a4, a5, lb = 999999999, ub = -999999999;
    scanf("%d%d%d%d%d", &a1, &a2, &a3, &a4, &a5);
    for (int i = -50; i <= 50; ++i) {
        cubic[i + 50] = i * i * i;
    }
    for (int i = -50; i <= 50; ++i) {
        if (i) {
            for (int j = -50; j <= 50; ++j) {
                if (j) {
                    int val = a1 * cubic[i + 50] + a2 * cubic[j + 50];
                    if (val < lb) {
                        lb = val;
                    }
                    if (val > ub) {
                        ub = val;
                    }
                    ++cnt[hash(val)];
                }
            }
        }
    }
    for (int i = -50; i <= 50; ++i) if (i) { 
        for (int j = -50; j <= 50; ++j)  if (j) {
            for (int k = -50; k <= 50; ++k) if (k) {
                int val = -a3 * cubic[i + 50] - a4 * cubic[j + 50] - a5 * cubic[k + 50];
                if (lb <= val && val <= ub) {
                    ans += cnt[hash (val)];
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
