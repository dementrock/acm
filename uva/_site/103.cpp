#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;

int k, n, box[100][100], map[100][100], max_length[100], max_list[100][100], visited[100];

int input_data(){
    if (scanf("%d%d", &k, &n) == EOF) {
        return 0;
    }
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &box[i][j]);
        }
        sort(box[i] + 1, box[i] + n + 1);
    }
    return 1;
}

int is_less(int boxa[], int boxb[]) {
    for (int i = 1; i <= n; ++i) {
        if (boxa[i] >= boxb[i]) {
            return 0;
        }
    }
    return 1;
}

void search(int node) {
    visited[node] = 1;
    int max_len = -1, max_i = 0;
    for (int i = 0; i <= k; ++i) {
        if (map[node][i]) {
            if (!visited[i]) {
                search(i);
            }
            if (max_length[i] > max_len) {
                max_len = max_length[i];
                max_i = i;
            }
        }
    }
    if (max_len == -1) {
        max_length[node] = 1;
        max_list[node][1] = node;
    }
    else {
        max_length[node] = ++max_len;
        max_list[node][1] = node;
        for (int i = 2; i <= max_len; ++i) {
            max_list[node][i] = max_list[max_i][i - 1];
        }
    }
    //printf("%d %d\n", node, max_length[node]);
}

void calc() {
    memset(max_length, 0, sizeof(max_length));
    memset(max_list, 0, sizeof(max_list));
    memset(visited, 0, sizeof(visited));
    memset(map, 0, sizeof(map));

    for (int i = 1; i <= k; ++i) {
        map[0][i] = 1;
        for (int j = 1; j <= k; ++j) {
            if (is_less(box[i], box[j])) {
                map[i][j] = 1;
                //printf("map: %d %d\n", i, j);
            }
        }
    }
    search(0);
}

void print() {
    printf("%d\n", max_length[0] - 1);
    for (int i = 2; i < max_length[0]; ++i) {
        printf("%d ", max_list[0][i]);
    }
    printf("%d\n", max_list[0][max_length[0]]);
}

int main(){
    while(input_data()){
        calc();
        print();
    }
    return 0;
}
