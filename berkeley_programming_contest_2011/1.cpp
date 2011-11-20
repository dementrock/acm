#include "contest.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
double fabs(double x) {
    return x >= 0 ? x : -x;
}
int zero(double x) {
    return fabs(x) < 1e-10;
}
int equal(double x, double y) {
    return zero(x-y);
}

int inputlist[10000001] = {}, anslist[10000001] = {}, cntans = 0;
int main(){
//    freopen("test.in", "r", stdin);
    int cnt = 0, a, lower, upper;
    double mindif = -1;
    double sum = 0;
    double average = 0;
    while (scanf("%d", &a) != EOF) {
        sum += a;
        inputlist[++cnt] = a;
    }
    average = sum * 1.0 / cnt;
    for (int i = 1; i <= cnt; ++i) {
        if (equal(mindif, -1) || fabs(average - inputlist[i]) < mindif) {
            mindif = fabs(average - inputlist[i]);
            cntans = 0;
            anslist[++cntans] = inputlist[i];
        }
        else if (equal(mindif, fabs(average - inputlist[i]))) {
            anslist[++cntans] = inputlist[i];
        }
    }
    if (cntans == 1) {
        printf("%d\n", anslist[1]);
    } else {
        printf("%d %d\n", min(anslist[1], anslist[2]), max(anslist[1], anslist[2]));
    }
    exit(0);
}
