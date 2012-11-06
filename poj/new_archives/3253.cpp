#include<iostream>
#include<algorithm>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

vector<int> v;

int main() {
    int n, l;
    long long ans = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &l);
        v.push_back(l);
    }
    make_heap(v.begin(), v.end(), greater<int>());
    for (int i = 1, a, b; i <= n - 1; ++i) {
        a = v.front();
        pop_heap(v.begin(), v.end(), greater<int>()); v.pop_back();
        b = v.front();
        pop_heap(v.begin(), v.end(), greater<int>()); v.pop_back();
        ans += a + b;
        v.push_back(a + b);
        push_heap(v.begin(), v.end(), greater<int>());
    }
    printf("%lld\n", ans);
    return 0;
}
