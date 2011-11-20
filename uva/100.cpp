#include<stdio.h>
#include<iostream>
#include<algorithm>
#define MAX 1000000
using namespace std;
int len_set[MAX + 1] = {};
int max_len_set[MAX * 8] = {};
int max_id = 0;

int calc_length(long long n){
    if (n <= MAX && len_set[n]) {
        return len_set[n];
    }
    int ans;
    if (n == 1) {
        ans = 1;
    }
    else {
        if (n & 1) {
            ans = 1 + calc_length(3 * n + 1);
        }
        else {
            ans = 1 + calc_length(n / 2);
        }
    }
    if (n <= MAX) {
        len_set[n] = ans;
    }
    return ans;
}

void generate_len_set(){
    for (int i = MAX; i >= 1; --i){
        if (!len_set[i]) {
            calc_length(i);
        }
    }
}

int generate_segment_tree(int id, int tree_left, int tree_right) {
    max_id = max(max_id, id);
    if (tree_left == tree_right) {
        return max_len_set[id] = len_set[tree_left];
    }
    else {
        int tree_mid = (tree_left + tree_right) / 2;
        return max_len_set[id] = max(generate_segment_tree(id * 2, tree_left, tree_mid), generate_segment_tree(id * 2 + 1, tree_mid + 1, tree_right));
    }
}

int get_max_len(int id, int left, int right, int tree_left, int tree_right) {
    if (left == tree_left && right == tree_right) {
        return max_len_set[id];
    }
    int tree_mid = (tree_left + tree_right) / 2;
    if (right <= tree_mid) {
        return get_max_len(id * 2, left, right, tree_left, tree_mid);
    }
    else if (left >= tree_mid + 1){
        return get_max_len(id * 2 + 1, left, right, tree_mid + 1, tree_right);
    }
    else{
        return max(get_max_len(id * 2, left, tree_mid, tree_left, tree_mid),
                   get_max_len(id * 2 + 1, tree_mid + 1, right, tree_mid + 1, tree_right));
    }
}

int main(){
    generate_len_set();
    generate_segment_tree(1, 1, MAX);
    int left = 0, right = 0;
    while (scanf("%d%d", &left, &right) != EOF){
        printf("%d %d %d\n", left, right, get_max_len(1, min(left, right), max(left, right), 1, MAX));
    }
    return 0;
}
