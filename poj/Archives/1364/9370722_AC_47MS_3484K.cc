#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXM 100001
#define MAXN 1001
#define INFTY 0x77777777
using namespace std;

int n, m;

struct Edge
{
	int v;
	double w;
	Edge *next;
} *edge[MAXM+1],mempool[MAXM+1];

int vis[MAXN+1],que[MAXN+1],cnt_vis[MAXN+1], cnt_elements[MAXN + 1], dis[MAXN + 1], memnum;

void add(int u, int v, double w)
{
	Edge *e=&mempool[++memnum];
	e->v=v;
	e->w=w;
	e->next=edge[u];
	edge[u]=e;
}

void init() {
    memset(dis, 0, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(que, 0, sizeof(que));
    memset(cnt_vis, 0, sizeof(cnt_vis));
    memset(cnt_elements, 0, sizeof(cnt_elements));
    memnum = 0;
    memset(edge, 0, sizeof(edge));
    memset(mempool, 0, sizeof(mempool));
}

int spfa()
{
    int start = 0, end = n + 1;
    
    for (int i = start + 1; i <= end; ++i) {
        dis[i] = INFTY;
    }
    vis[start] = 1;
    que[0] = start;
    cnt_vis[start] = 1;
    int tail = -1, head = 0, cnt_elements = 1;
    while (cnt_elements) {
        tail = (tail + 1) % (end + 1);
        --cnt_elements;
        int now = que[tail];
        if (cnt_vis[now] > 2 * end) {
            return 1;
        }
        for (Edge *e = edge[now]; e != NULL; e = e -> next) {
            int new_len = e -> w + dis[now];
            int to = e -> v;
            if (new_len < dis[to]) {
                dis[to] = new_len;
                if (!vis[to]) {
                    ++cnt_elements;
                    head = (head + 1) % (end + 1);
                    vis[to] = 1;
                    que[head] = to;
                    ++cnt_vis[to];
                    if (cnt_vis[to] > 2 * end) {
                        return 1;
                    }
                }
            }
        }
        vis[now] = 0;
    }
    return 0;
}



int input(){
    init();
    cin >> n;
    if (!n) {
        return 0;
    }
    cin >> m;
    int si, ni, ki;
    string oi;
    for (int i = 1; i <= m; ++i) {
        cin >> si >> ni >> oi >> ki;
        if (oi == "lt") {
            add(si, si + ni + 1, ki - 1);
        }
        else {
            add(si + ni + 1, si, - ki - 1);
        }
    }
    return 1;
}

void calc(){
    for (int i = 1; i <= n + 1; ++i) {
        add(0, i, 0);
    }
    int is_loop = spfa();
    if (is_loop) {
        puts("successful conspiracy");
    } else {
        puts("lamentable kingdom");
    }
}

int main(){
    /*freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout); */
    while(input()){
        calc();
    }
    return 0;
}