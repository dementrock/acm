#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cntflake, flake[200000][6], n; 

int minrep(int s[], int len) {
    int i = 0;
    for (int j = 1, k = 0; i < len && j < len && k < len; ){
        int x = (i + k) % len, y = (j + k) % len;
        if (s[x] == s[y]) {
            ++k;
        } else {
            if (s[x] > s[y]) {
                i += k + 1;
                j = i + 1;
            } else {
                j += k + 1;
            }
            k = 0;
        }
    }
    return i;
}

void add_flake(int len[]) {
    int clockwise[20] = {}, counterwise[20] = {};
    for (int i = 0; i < 6; ++i) {
        clockwise[i] = clockwise[i + 6] = len[i];
        counterwise[i] = counterwise[i + 6] = len[5 - i];
    }
    int pos1 = minrep(clockwise, 6), pos2 = minrep(counterwise, 6);
    int min1[6] = {}, min2[6] = {};
    int choosecounter = 0;
    for (int i = 0; i < 6; ++i) {
        if (clockwise[pos1 + i] > counterwise[pos2 + i] ) {
            choosecounter = 1;
            break;
        } else if (clockwise[pos1 + i] < counterwise[pos2 + i]) {
            break;
        }
    }
    if (choosecounter) {
        for (int i = 0; i < 6; ++i) {
            flake[cntflake][i] = counterwise[pos2 + i];
        }
    } else {
        for (int i = 0; i < 6; ++i) {
            flake[cntflake][i] = clockwise[pos1 + i];
        }
    }
    ++cntflake;
} 

int cmp(const void *a, const void *b){
    int *x = (int *)a, *y = (int *)b;
    for (int i = 0; i < 6; ++i) {
        if (x[i] < y[i]) {
            return -1;
        } else if (x[i] > y[i]) {
            return 1;
        }
    }
    return 0;
}

int main(){
    scanf("%d", &n);
    int akelen[10];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            scanf("%d", &akelen[j]);
        }
        add_flake(akelen);
    }
    qsort(flake, cntflake, sizeof(flake[0]), cmp);
    int is_same;
    for (int i = 0; i < cntflake - 1; ++i) {
        is_same = 1;
        for (int j = 0; j < 6; ++j) {
            if (flake[i][j] != flake[i + 1][j]) {
                is_same = 0;
                break;
            }
        }
        if (is_same) {
            break;
        }
    }
    if (is_same) {
        printf("Twin snowflakes found.\n");
    } else {
        printf("No two snowflakes are alike.\n");
    }
    return 0;
}
