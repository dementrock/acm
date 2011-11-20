#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#define MAXN 201
using namespace std;

struct edge{
    int x, y;
    double l;
} e[20001];

int cnt_e = 0, n, father[MAXN];

double x[MAXN], y[MAXN], ans; 

void init(){
    cnt_e = 0;
    memset(e, 0, sizeof(e));
    ans = 0;
    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    memset(father, 0, sizeof(father));
}

void input(){
    cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> x[i] >> y[i];
    }
}

double calcdis(double x1, double y1, double x2, double y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void add_edge(int x, int y, double l){
    e[++cnt_e].x = x;
    e[cnt_e].y = y;
    e[cnt_e].l = l;
}

void swap(edge &a, edge &b)
{
        edge x=a;a=b;b=x;
}
int partition(edge a[], int left, int right)
{
        int i=left+right>>1,j;
            swap(a[i],a[right]);
                for(j=left,i=left-1;j<right;++j)
                            if(a[j].l<a[right].l)
                                            swap(a[++i],a[j]);
                    swap(a[++i],a[right]);
                        return i;
}
void quicksort(edge a[], int left, int right)
{
        if(left>=right) return;
            int i=partition(a,left,right);
                quicksort(a,left,i-1);
                    quicksort(a,i+1,right);
}

int getfather(int x){
    if (father[x] == x) {
        return x;
    }
    return father[x] = getfather(father[x]);
}

void merge(int x, int y, double l){
    int a = getfather(x), b = getfather(y);
    if (a != b) {
        ans += l;
        father[a] = b;
    }
}

void kruskal(){
    for (int i = 1; i <= cnt_e; ++i){
        merge(e[i].x, e[i].y, e[i].l);
    }
}

void calc(){
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
    }

    for (int i = 1; i <= n; ++i){
        for (int j = i + 1; j <= n; ++j){
            add_edge(i, j, calcdis(x[i], y[i], x[j], y[j]));
        }
    }
    quicksort(e, 1, cnt_e);
    kruskal();
}

void print(){
    printf("%.2lf\n", ans);
}

int main(){
    int cases;
    cin >> cases;
    for (int i = 1; i <= cases; ++i){
        init();
        input();
        calc();
        print();
        if (i != cases) {
            printf("\n");
        }
    }
    return 0;
}
