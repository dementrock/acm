#include"contest.h"
#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

struct ForSort {
    int pos, cnt;
} appeared[1000];


int cnt_calc[100] = {1,3,3,5,5,5,7,7,7,7,7,9,9,9,9,9,9,9,9,11,11,11,11,11,11,11};

int strmap[1000];

string strlist[1001]; int cnt;

char str[10001];

void swap(ForSort &a, ForSort &b) {
    ForSort x = a; a = b; b = x;
}

void generate(int len, string s) {
    if (!len) {
        strlist[++cnt] = s;
        return;
    }
    generate(len - 1, s + "-");
    generate(len - 1, s + ".");
}

void swap(string &a, string &b) {
    string x = a; a = b; b = x;
}

int calc(string s){
    int res = 0;
    for (int i = 0; i < s.length(); ++i) {
        res += s[i] == '.' ? 1 : 3; 
    }
    res += s.length() - 1;
    return res;
} 

void init() {
    for (int i = 1; i <= 8; ++i) {
        generate(i, "");
    }
    for(int i = 1; i <= cnt; ++i) {
        for(int j = i + 1; j <= cnt; ++j) {
            if (calc(strlist[i]) > calc(strlist[j])) {
                swap(strlist[i], strlist[j]);
            }
        }
    }
    for (int i = 1; i <= 26; ++i) {
        cnt_calc[i - 1] = calc(strlist[i]);
    }
} 


int calc_total() {
    int res = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == ' ') {
            res += 7;
        } else {
            res += cnt_calc[strmap[str[i] - 'A']];
            if (i > 0 && str[i - 1] != ' ') {
                res += 3;
            }
        }
    }
    return res;
}

int work() {
    for (int i = 0; i < 26; ++i) {
        appeared[i].pos = i;
        appeared[i].cnt = 0;
    }
    for (int i = 0; i < strlen(str); ++i) {
        ++appeared[str[i] - 'A'].cnt;
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = i + 1; j < 26; ++j) {
            if (appeared[i].cnt < appeared[j].cnt) {
                swap(appeared[i], appeared[j]);
            }
        }
    }
    for (int i = 0; i < 26 && appeared[i].cnt; ++i) {
        strmap[appeared[i].pos] = i;
    }
    return calc_total();
}

int main() {
    while(cin.getline(str, 10000)) {
        printf("%d\n", work());
        memset(str, 0, sizeof(str));
    }
    exit(0);
}
