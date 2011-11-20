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
        int *dis, *vis, *que, *cnt_vis;
        int is_runned;
        int is_neg_loop;
        void run(int start, int end, Edge **edge);
        int get_distance(int end);
        void reset();
        void init(int max_nodes);
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
    spfa.init(_max_nodes);
}

void Graph::add_directed_edge(int start, int end, int len) {
    //printf("%d %d %d\n", start, end, len);
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

void Graph::Spfa::init(int max_nodes) {
    dis = new int[max_nodes];
    vis = new int[max_nodes];
    que = new int[max_nodes];
    cnt_vis = new int[max_nodes];
    memset(dis, 0, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(que, 0, sizeof(que));
    memset(cnt_vis, 0, sizeof(cnt_vis));
}

void Graph::Spfa::run(int start, int end, Edge **edge) { // Assume that the nodes are start, start + 1, ..., end - 1, end
    //printf("%d %d\n", start, end);
    for (int i = start; i <= end; ++i) {
        dis[i] = vis[i] = que[i] = cnt_vis[i] = 0;
    }
    for (int i = start + 1; i <= end; ++i) {
        dis[i] = INFTY;
    }
    vis[start] = 1;
    que[0] = start;
    cnt_vis[start] = 1;
    int tail = -1, head = 0;
    int proceed = 1;
    while (proceed) {
        proceed = 0;
        tail = (tail + 1) % (end + 1);
        int now = que[tail];
        //cout << "now " << now << endl;
        if (cnt_vis[now] > end) {
            is_neg_loop = 1;
            return;
        }
        for (Edge *e = edge[now]; e != NULL; e = e -> next) {
            int new_len = e -> len + dis[now];
            //cout << now << " " << e -> end << " " << e -> len << endl;
            if (new_len < dis[e -> end]) {
                //cout << "yes" << endl;
                proceed = 1;
                dis[e -> end] = new_len;
                if (!vis[e -> end]) {
                    head = (head + 1) % (end + 1);
                    vis[e -> end] = 1;
                    que[head] = e -> end;
                    ++cnt_vis[e -> end];
                    if (cnt_vis[e -> end] > end) {
                        is_neg_loop = 1;
                        return;
                    }
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
    is_runned = 0;
    is_neg_loop = 0;
    memset(dis, 0, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(que, 0, sizeof(que));
    memset(cnt_vis, 0, sizeof(cnt_vis));
}

Graph g(MAXN, MAXM);


int input(){
    g.reset();
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
            g.add_directed_edge(si, si + ni + 1, ki - 1);
        }
        else {
            g.add_directed_edge(si + ni + 1, si, - ki - 1);
        }
    }
    return 1;
}

void calc(){
    for (int i = 1; i <= n + 1; ++i) {
        g.add_directed_edge(0, i, 0);
    }
    g.run_spfa(0, n + 1);
    if (g.spfa.is_neg_loop) {
        puts("successful conspiracy");
    } else {
        puts("lamentable kingdom");
    }
}

int main(){
/*    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout); */
    while(input()){
        calc();
    }
    return 0;
}
