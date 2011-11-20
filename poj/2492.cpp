#include<stdio.h>
#include<stdlib.h>
#define MAXN 2000

int father[MAXN + 1], is_dif[MAXN + 1], is_found;

int getfather(int x) {
    if (father[x] == x) {
        return x;
    } else {
        //return getfather(father[x]);
        getfather(father[x]);
        is_dif[x] ^= is_dif[father[x]]; 
        return father[x] = getfather(father[x]);
    }
}

int dif(int x) {
    if (father[x] == x) {
        return 0;
    } else {
        return is_dif[x] ^ dif(father[x]);
    }
}
void check(int x, int y) {
    if (getfather(x) == getfather(y)) {
        if (is_dif[x] == is_dif[y]) {
            is_found = 1;
        }
    } else {
        int tmp_father = getfather(y);
        father[getfather(y)] = getfather(x);
        is_dif[tmp_father] = 1 - (is_dif[y] ^ is_dif[x]);
    }
}
void init() {
    int n, k, x, y;
    is_found = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
        is_dif[i] = 0;
    }
    for (int i = 1; i <= k; ++i) {
        scanf("%d%d", &x, &y);
        check(x, y);
        /*printf("Father: ");
        for (int i = 1; i <= n; ++i) {
            printf("%d ", father[i]);
        }
        printf("\nIs different: ");
        for (int i = 1; i <= n; ++i) {
            printf("%d ", is_dif[i]);
        }
        printf("\n");*/
    }
}
int main() {
//    freopen("test.in", "r", stdin);
    int cases;
    scanf("%d", &cases);
    for (int i = 1; i <= cases; ++i) {
        init();
        printf("Scenario #%d:\n", i);
        if (is_found) {
            printf("Suspicious bugs found!\n\n");
        } else {
            printf("No suspicious bugs found!\n\n");
        }
    }
    return 0;
}
