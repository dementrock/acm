#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXN 1010
using namespace std;

char pretree[100001], intree[100001];

void print_tree(int pre_left, int pre_right, int in_left, int in_right) {
    //printf("%d %d %d %d\n", pre_left, pre_right, in_left, in_right);
    // the first element in pre is the root
    if (pre_left > pre_right) {
        return;
    }
    int root_pos;
    for (root_pos = in_left; root_pos <= in_right; ++root_pos) {
        if (intree[root_pos] == pretree[pre_left]) {
            break;
        }
    }
    //printf("%d\n", root_pos);
    //getchar();
    print_tree(pre_left + 1, pre_left + (root_pos - in_left), in_left, root_pos - 1);
    print_tree(pre_left + (root_pos - in_left) + 1, pre_right, root_pos + 1, in_right);
    printf("%c", intree[root_pos]);
}

int main() {
    while (scanf("%s%s", pretree, intree) != EOF) {
        print_tree(0, strlen(pretree) - 1, 0, strlen(pretree) - 1);
        printf("\n");
    }
    return 0;
}

