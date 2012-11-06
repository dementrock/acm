#include<iostream>
#include<string>
#include<map>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

map<string, string> dict;

char s1[101], s2[101];

int main() {
    while (1) {
        scanf("%s%s", s1, s2);
        dict[string(s2)] = string(s1);
        getchar();
        char c = getchar();
        if (c == '\n') {
            break;
        }
        ungetc(c, stdin);
    }
    while (scanf("%s", s2) != EOF) {
        if (dict[string(s2)] == "") {
            printf("eh\n");
        } else {
            printf("%s\n", dict[string(s2)].c_str());
        }
    }
    return 0;
}
