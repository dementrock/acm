#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 50000
struct Edge
{
	int v;
	long long w;
	Edge *next;
} *edge[MAXN+1],mempool[MAXN*2+1];
int maxmem=0,que[MAXN+1],vis[MAXN+1],n,m;
long long ans,dis[MAXN+1],w[MAXN+1],oo;
void add(int u, int v, long long w)
{
	Edge *e=&mempool[++maxmem];
	e->v=v;
	e->w=w;
	e->next=edge[u];
	edge[u]=e;
}
void init()
{
	int x,y;
	long long z;
	ans=0;
	maxmem=0;
	memset(edge,0,sizeof(edge));
	memset(w,0,sizeof(w));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%I64d",&w[i]);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%I64d",&x,&y,&z);
		if(x==y) continue;
		add(x,y,z);
		add(y,x,z);
	}
}
void spfa(int s)
{
	memset(dis,0x77,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(que,0,sizeof(que));
	int closed=-1,open=0;
	que[0]=s;
	vis[s]=true;
	dis[s]=0;
	while(closed!=open)
	{
		closed=(closed+1)%n;
		int now=que[closed];
		for(Edge *tmp=edge[now];tmp!=NULL;tmp=tmp->next)
		{
			if(dis[now]+tmp->w<dis[tmp->v])
			{
				dis[tmp->v]=dis[now]+tmp->w;
				if(!vis[tmp->v])
				{
					vis[tmp->v]=true;
					open=(open+1)%n;
					que[open]=tmp->v;
				}
			}
		}
		vis[now]=false;
	}
}
void work()
{
	if(n<=1)
	{
		printf("0\n");
		return;
	}
	spfa(1);
	for(int i=2;i<=n;++i)
	{
		if(dis[i]>=oo)
		{
			printf("No Answer\n");
			return;
		}
		ans+=dis[i]*w[i];
	}
	printf("%I64d\n",ans);
}
int main()
{
	int t;
	memset(&oo,0x77,sizeof(oo));
	scanf("%d",&t);
	while(t--)
	{
		init();
		work();
	}
	return 0;
}
