#include"contest.h"
#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

struct Num {
    int x, y;
};

int seq[100], len_seq;

void turn_right() {
    if (len_seq & 1) {
        ++seq[len_seq];
    } else {
        --seq[len_seq];
        seq[++len_seq] = 2;
    }
}

void turn_left() {
    if (len_seq & 1) {
        --seq[len_seq];
        seq[++len_seq] = 2;
    } else {
        ++seq[len_seq];
    }
}

void calc_ans() {
    Num res;
    res.x = 1, res.y = seq[len_seq];
    for (int i = len_seq - 1; i >= 1; --i) {
        res.x = seq[i] * res.y + res.x;
        int tmp = res.x; res.x = res.y, res.y = tmp;
    }
    printf("%d/%d\n", res.y, res.x);
}

int main() {
    char route[100];
    while(gets(route)) {
        memset(seq, 0, sizeof(seq));
        len_seq = 0;
        seq[++len_seq] = 1;
        int level = strlen(route);
        if (!level) {
            printf("1/1\n");
            continue;
        }
        for (int i = 0; i < level; ++i) {
            if (route[i] == 'R') {
                turn_right();
            } else {
                turn_left();
            }
        }
        calc_ans();
    }
    exit(0);
}
