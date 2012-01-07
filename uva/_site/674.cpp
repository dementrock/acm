#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;

int f[5][10000], coins[] = {1, 5, 10, 25, 50};

void calc(){
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j <= 7489; ++j) {
            if (!i) {
                f[i][j] = 1;
            } else {
                f[i][j] = f[i - 1][j];
                if (j - coins[i] >= 0) {
                    f[i][j] += f[i][j - coins[i]];
                }
            }
        }
    }
}

int main(){
    calc();
    int n;
    while(scanf("%d", &n) != EOF) {
        printf("%d\n", f[4][n]);
    }
    return 0;
}
