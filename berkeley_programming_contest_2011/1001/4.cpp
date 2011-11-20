#include"contest.h"
#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

struct Stacker {
    string s;
    char last_op;
    int is_single;
} stacker[10001];

int cnt = 0;

int main() {
    char inputline[10000];
    while (gets(inputline)) {
        int cnt = 0;
        for (int i = 0; i < strlen(inputline); ++i) {
            char now = inputline[i];
            if (now == ' ') {
                continue;
            }
            if ('0' <= now && now <= '9') {
                stacker[++cnt].s = now;
                stacker[cnt].last_op = 0;
                stacker[cnt].is_single = 1;
            } else if (now == '_') {
                if (stacker[cnt].is_single) {
                    stacker[cnt].s = "-" + stacker[cnt].s;
                    stacker[cnt].last_op = '_';
                } else {
                    stacker[cnt].s = "-(" + stacker[cnt].s + ")";
                    stacker[cnt].last_op = '_';
                }
            } else if (now == '+') {
                if (stacker[cnt].is_single) {
                    stacker[cnt - 1].s = stacker[cnt - 1].s + now + stacker[cnt].s;
                    
                } else if (stacker[cnt - 1].is_single && !stacker[cnt].is_single) {
                    if (stacker[cnt].last_op == '+' || stacker[cnt].last_op == '-') {
                        stacker[cnt].s = "(" + stacker[cnt].s + ")";
                    }
                    stacker[cnt - 1].s = stacker[cnt - 1].s + now + stacker[cnt].s;
                } else { // Both are not single expression
                    if (stacker[cnt].last_op == '+' || stacker[cnt].last_op == '-') {
                        stacker[cnt - 1].s = stacker[cnt - 1].s + now + "(" + stacker[cnt].s + ")";
                    } else if (stacker[cnt].last_op == '*' || stacker[cnt].last_op == '/' || stacker[cnt].last_op == '-') {
                        stacker[cnt - 1].s = stacker[cnt - 1].s  + now + stacker[cnt].s;
                    }
                }
                stacker[cnt - 1].is_single = 0;
                stacker[cnt - 1].last_op = now;
                --cnt;
            } else if (now == '-') {
                if (stacker[cnt].is_single) {
                    stacker[cnt - 1].s = stacker[cnt - 1].s + now + stacker[cnt].s;
                } else if (stacker[cnt - 1].is_single && !stacker[cnt].is_single) {
                    if (stacker[cnt].last_op == '+' || stacker[cnt].last_op == '-') {
                        stacker[cnt].s = "(" + stacker[cnt].s + ")";
                    }
                    stacker[cnt - 1].s = stacker[cnt - 1].s + now + stacker[cnt].s;
                } else { // Both are not single expression
                    if (stacker[cnt].last_op == '+' || stacker[cnt].last_op == '-') {
                        stacker[cnt - 1].s = stacker[cnt - 1].s + now + "(" + stacker[cnt].s + ")";
                    } else if (stacker[cnt].last_op == '*' || stacker[cnt].last_op == '/' || stacker[cnt].last_op == '-') {
                        stacker[cnt - 1].s = stacker[cnt - 1].s  + now + stacker[cnt].s;
                    }
                }
                stacker[cnt - 1].is_single = 0;
                stacker[cnt - 1].last_op = now;
                --cnt;
            } else if (now == '*' || now == '/') {
                if (stacker[cnt].is_single) {
                    if (stacker[cnt - 1].last_op == '+' || stacker[cnt - 1].last_op == '-') {
                        stacker[cnt - 1].s = "(" + stacker[cnt - 1].s + ")";
                    }
                    stacker[cnt - 1].s = stacker[cnt - 1].s + now + stacker[cnt].s;
                } else if (stacker[cnt - 1].is_single && !stacker[cnt].is_single) {
                    stacker[cnt - 1].s = stacker[cnt - 1].s + now + "(" + stacker[cnt].s + ")";
                } else { // Both are not single expression
                    if (stacker[cnt - 1].last_op == '+' || stacker[cnt - 1].last_op == '-') {
                        stacker[cnt - 1].s = "(" + stacker[cnt - 1].s + ")";
                    }
                    stacker[cnt - 1].s = stacker[cnt - 1].s  + now + "(" + stacker[cnt].s + ")";
                }
                stacker[cnt - 1].is_single = 0;
                stacker[cnt - 1].last_op = now;
                --cnt;
            }
        }
        cout << stacker[cnt].s << endl;
    }
    exit(0);
}
