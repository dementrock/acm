#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;

int t[100], test[100], c[100], correct[100], f[100][100], n;

int input_data(){
    memset(f, 0xff, sizeof(f));
    for (int i = 1; i <= n; ++i){
        if (scanf("%d", &t[i]) == EOF) {
            return 0;
        }
        test[t[i]] = i;
    }
    return 1;
}

int calc(int i, int j) {
    if (f[i][j] >= 0) {
        return f[i][j];
    }
    if (!i || !j) {
        return f[i][j] = 0;
    }
    if (correct[i] == test[j]) {
        return f[i][j] = 1 + calc(i - 1, j - 1);
    }
    return f[i][j] = max(calc(i, j - 1), calc(i - 1, j));
}

int main(){
    scanf("%d\n", &n);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &c[i]);
        correct[c[i]] = i;
    }
    while(input_data()){
        printf("%d\n", calc(n, n));
    }
    return 0;
}
