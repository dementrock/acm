#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXM 100001
#define MAXN 1001
#define INFTY 0x77777777
using namespace std;

class Graph {
public:
    Graph();
    Graph(int max_nodes, int max_edges);
    void add_directed_edge(int start, int end, int len);
    void add_undirected_edge(int node1, int node2, int len);
    void run_spfa(int start, int end);
    void print(int start, int end);
    void reset();

    class Edge {
    public:
        int end, len;
        Edge *next;
    };
    Edge **edge, *mempool;
    int memnum;

    class Spfa {
    public:
        Spfa();
        int *dis;
        int is_runned;
        int is_neg_loop;
        void run(int start, int end, Edge **edge);
        int get_distance(int end);
        void reset();
    };

    Spfa spfa;
private:
    int _max_nodes, _max_edges;
};

Graph::Graph(int max_nodes, int max_edges) {
    edge = new Edge* [max_nodes];
    mempool = new Edge[max_edges];
    memset(edge, 0, sizeof(edge));
    memset(mempool, 0, sizeof(mempool));
    memnum = 0;
    _max_nodes = max_nodes, _max_edges = max_edges;
}

void Graph::add_directed_edge(int start, int end, int len) {
    Edge *e = &mempool[++memnum];
    e -> end = end ;
    e -> len = len;
    e -> next = edge[start];
    edge[start] = e;   
}

void Graph::add_undirected_edge(int node1, int node2, int len) {
    add_directed_edge(node1, node2, len);
    add_directed_edge(node2, node1, len);
}

void Graph::run_spfa(int start, int end) {
    spfa.run(start, end, edge);
}

void Graph::reset() {
    for (int i = 0; i < _max_nodes; ++i) {
        edge[i] = NULL;
    }
    memset(edge, 0, sizeof(edge));
    memset(mempool, 0, sizeof(mempool));
    memnum = 0;
    spfa.reset();
}

Graph::Spfa::Spfa() {
    is_runned = 0;
    is_neg_loop = 0;
}

void Graph::Spfa::run(int start, int end, Edge **edge) { // Assume that the nodes are start, start + 1, ..., end - 1, end
    dis = new int[end + 1];
    int *vis = new int[end + 1];
    int *que = new int[end + 1];
    int *cnt_vis = new int[end + 1];
    memset(dis, 0, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(que, 0, sizeof(que));
    memset(cnt_vis, 0, sizeof(cnt_vis));
    for (int i = start + 1; i <= end; ++i) {
        dis[i] = INFTY;
    }
    vis[start] = 1;
    que[0] = start;
    int tail = -1, head = 0;
    while (tail != head) {
        tail = (tail + 1) % end;
        int now = que[tail];
        if (cnt_vis[now] > end) {
            is_neg_loop = 1;
            return;
        }
        for (Edge *e = edge[now]; e != NULL; e = e -> next) {
            int new_len = e -> len + dis[now];
            if (new_len < dis[e -> end]) {
                dis[e -> end] = new_len;
                if (!vis[e -> end]) {
                    head = (head + 1) % end;
                    vis[e -> end] = 1;
                    que[head] = e -> end;
                    ++cnt_vis[e -> end];
                }
            }
        }
        vis[now] = 0;
    }
    is_runned = 1;
}

int Graph::Spfa::get_distance(int end) {
    if (is_runned) {
        return dis[end];
    } else {
        return -1;
    }
}

void Graph::Spfa::reset() {
    delete [] dis;
    dis = NULL;
    is_runned = false;
    is_neg_loop = false;
}

int n, k, stop[101][101], is_stopped[101][101], t[101], ans;

Graph g(MAXN, MAXM);

int point(int i, int j) {
    return (i - 1) * 100 + j + 1;
}

int input(){
    g.reset();
    memset(stop, 0, sizeof(stop));
    memset(is_stopped, 0, sizeof(is_stopped));
    memset(t, 0, sizeof(t));
    if (scanf("%d %d\n", &n, &k) == EOF) {
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &t[i]);
    }
    scanf("\n");
    for(int i = 1; i <= n; ++i){
        char tmp_line[1000] = {};
        gets(tmp_line);
        for (int j = 0, num = 0; j < strlen(tmp_line); ++j) {
            if (tmp_line[j] == ' ' || j == strlen(tmp_line) - 1) {
                if (j == strlen(tmp_line) - 1) {
                    num = num * 10 + tmp_line[j] - '0';
                }
                stop[i][++stop[i][0]] = num;                
                num = 0;
            }
            else {
                num = num * 10 + tmp_line[j] - '0';
            }
            is_stopped[i][stop[i][stop[i][0]]] = 1;
        }
    }
    return 1;
}

void calc(){
    /* create edges for the same elevator */
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < stop[i][0]; ++j) {
            g.add_undirected_edge(point(i, stop[i][j]), point(i, stop[i][j + 1]), t[i] * (stop[i][j + 1] - stop[i][j]));
        }
    }
    for (int l = 0; l <= 99; ++l) {
        for (int i = 1; i <= n; ++i) {
            if (is_stopped[i][l]) {
                for (int j = i + 1; j <= n; ++j) {
                    if (is_stopped[j][l]) {
                        g.add_undirected_edge(point(i, l), point(j, l), 60);
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        g.add_undirected_edge(point(1, -1), point(i, 0), 0);
    }
    g.run_spfa(0, point(n, 100));
    
    ans = -1;
    for (int i = 1; i <= n; ++i) {
        if (g.spfa.get_distance(point(i, k)) < ans || ans == -1) {
            ans = g.spfa.get_distance(point(i, k));
        }
    }
}

void print(){
    if (ans == INFTY) {
        printf("IMPOSSIBLE\n");
    } else {
        printf("%d\n", ans);
    }
}
int main(){
    while(input()){
        calc();
        print();
    }
    return 0;
}
