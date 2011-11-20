#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define MAXN 100
#define MAXM 100
using namespace std;

int n, m;

char field[MAXN + 1][MAXM + 1], mine[MAXN + 1][MAXM + 1];

int input_data(){
    if (scanf("%d %d\n", &n, &m) == EOF) {
        return 0;
    }
    if (!n && !m) {
        return 0;
    }
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            scanf("%c", &field[i][j]);
        }
        scanf("\n");
    }
    return 1;
}

char calc_mine(int i, int j){
    if (field[i][j] == '*') {
        return field[i][j];
    }
    int res = 0;
    for (int delta_x = -1; delta_x <= 1; ++delta_x) {
        for (int delta_y = -1; delta_y <= 1; ++delta_y ) {
            if (delta_x || delta_y){
                int new_x = i + delta_x;
                int new_y = j + delta_y;
                if (1 <= new_x && new_x <= n && 1 <= new_y && new_y <= m) {
                    if (field[new_x][new_y] == '*') {
                        ++res;
                    }
                }
            }
        }
    }
    return res + '0';
}

void calc(){
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            mine[i][j] = calc_mine(i, j);
        }
    }
}

void print_result(int counter) {
    if (counter > 1) {
        printf("\n");
    }
    printf("Field #%d:\n", counter);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            printf("%c", mine[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int counter = 0;
    while(input_data()){
        ++counter;
        calc();
        print_result(counter);
    }
}
