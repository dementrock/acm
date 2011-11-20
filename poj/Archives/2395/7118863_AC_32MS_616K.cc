#include<stdio.h>
#include<string.h>
struct Edge
{
	int v,w;
	Edge *next;
} *edge[2010],mempool[20010];
int memnum,n,m,l,r,vis[2010];
inline int max(int a, int b)
{
	return a>b?a:b;
}
void add(int u, int v, int w)
{
	Edge *e=&mempool[++memnum];
	e->v=v;
	e->w=w;
	e->next=edge[u];
	edge[u]=e;
}
void init()
{
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
		r=max(r,z);
	}
}
void dfs(int now, int maxe)
{
	vis[now]=1;
	for(Edge *tmp=edge[now];tmp!=NULL;tmp=tmp->next)
		if(!vis[tmp->v]&&tmp->w<=maxe)
			dfs(tmp->v,maxe);
}
int judge(int k)
{
	memset(vis,0,sizeof(vis));
	dfs(1,k);
	for(int i=2;i<=n;++i) if(!vis[i]) return 0;
	return 1;
}
void work()
{
	int mid=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(!judge(mid))
			l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",l);
}
int main()
{
	init();
	work();
	return 0;
}
