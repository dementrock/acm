#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;

char str1[2000], str2[2000];

int f[2000][2000];

int input_data(){
    return gets(str1) && gets(str2);
}

int find(int i, int j) {
    if (f[i][j] >= 0) {
        return f[i][j];
    }
    if (!i || !j) {
        return f[i][j] = 0;
    }
    else if (str1[i - 1] == str2[j - 1]) {
        return f[i][j] = 1 + find(i - 1, j - 1);
    } else {
        return f[i][j] = max(find(i - 1, j), find(i, j - 1));
    }
}

int calc(){
    memset(f, 0xff, sizeof(f));
    return find(strlen(str1), strlen(str2));
}

int main(){
    while(input_data()){
        printf("%d\n", calc());
    }
    return 0;
}
