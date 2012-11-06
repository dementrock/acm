#include <iostream>
#include <queue>
using namespace std;
#define Maxn 1010
#define Maxm 5010
#define oo 1999999999

struct edges {
int node, v, next;
} edge[Maxm];
int node[Maxn];
int n, m;
int f[Maxn];

bool spfa(double mid) {
	double dis[Maxn];
	int i;
	bool visit[Maxn];
	int cnt[Maxn];
	memset(cnt, 0, sizeof (cnt));
	memset(visit, false, sizeof (visit));
	queue<int> Q;
	for (i = 1; i <= n; i++)
		dis[i] = oo;
	dis[1] = 0;
	Q.push(1);
	visit[1] = true;
	while (!Q.empty()) {
		int now = Q.front();
		Q.pop();
		visit[now] = false;
		for (i = node[now]; i != 0; i = edge[i].next) {
			if (dis[edge[i].node] > dis[now] + edge[i].v * mid - f[now]) {
				dis[edge[i].node] = dis[now] + edge[i].v * mid - f[now];
				if (!visit[edge[i].node]) {
					visit[edge[i].node] = true;
					if ((++cnt[edge[i].node] == n)) return false;
					Q.push(edge[i].node);
				}
			}
		}
	}
	return true;
}

int main() {
int i, a, b, v;
scanf("%d%d", &n, &m);
for (i = 1; i <= n; i++)
scanf("%d", &f[i]);
memset(node, 0, sizeof (node));
for (i = 1; i <= m; i++) {
scanf("%d%d%d", &a, &b, &v);
edge[i].next = node[a];
edge[i].node = b;
edge[i].v = v;
node[a] = i;
}
int left = 0, right = 1000000000, mid, ans;
while (left < right) {
mid = (left + right) / 2;
if (spfa(mid * 1.0 / 1000)) {
right = mid - 1;
} else left = mid + 1, ans = mid;
}
if (ans % 10 > 4) ans += 10 - ans % 10;
else ans -= ans % 10;
printf("%.2lf\n", ans * 1.0 / 1000);
}
