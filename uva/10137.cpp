#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#define MAXN 1000
using namespace std;

int n;
int expense[MAXN + 1];

int input_data(){
    int a, b;
    scanf("%d\n", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d.%d\n", &a, &b);
        expense[i] = a * 100 + b;
    }
    return n;
}

int calc() {
    int average = 0;
    for (int i = 1; i <= n; ++i) {
        average += expense[i]; 
    }
    average = int(((double)average / n) + 0.5);
    int change_back = 0, change_forward = 0;
    for (int i = 1; i <= n; ++i) {
        if (expense[i] >= average) {
            change_back += expense[i] - average;
        } else {
            change_forward += average - expense[i];
        }
    }
    return min(change_back, change_forward);
}

int main() {
    while(input_data()) {
        printf("$%.2lf\n", calc() * 0.01);
    }
    return 0;
}
