#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1000
#define MAXM 5000
struct Edge
{
	int v;
	double w;
	Edge *next;
} *edge[MAXM+1],mempool[MAXM+1];
int vis[MAXN+1],que[MAXN+1],c[MAXN+1],
map[MAXN+1][MAXN+1],
closed,Open,m,n,memnum;
double dis[MAXN+1],v[MAXN+1][MAXN+1],f[MAXN+1],l,r,mid,oo=1999999999;
void add(int u, int v, double w)
{
	Edge *e=&mempool[++memnum];
	e->v=v;
	e->w=w;
	e->next=edge[u];
	edge[u]=e;
}
int spfa(double mid)
{
	for(int i=1;i<=n;++i) dis[i]=oo;
	memset(vis,0,sizeof(vis));
	memset(c,0,sizeof(c));
	memset(que,0,sizeof(que));
	dis[1]=0;
	vis[1]=true;
	que[0]=1;
	closed=-1,Open=0;
	while(closed!=Open)
	{
		closed=(closed+1)%n;
		int now=que[closed];
		if(c[now]>n) return 0;
		for(Edge *tmp=edge[now];tmp!=NULL;tmp=tmp->next)
			if(dis[now]+tmp->w*mid-f[now]<dis[tmp->v])
			{
				dis[tmp->v]=dis[now]+tmp->w*mid-f[now];
			//	printf("%d %.3lf\n",i,dis[i]);
				if(!vis[tmp->v])
				{
					Open=(Open+1)%n;
					vis[tmp->v]=true;
					que[Open]=tmp->v;
					++c[tmp->v];
					if(c[tmp->v]>n) return 0;
				}
			}
		vis[now]=false;
	}
	return 1;
}
void init()
{
	int x,y;
	double z;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lf",&f[i]);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%lf",&x,&y,&z);
		add(x,y,z);
		v[x][y]=z;
		map[x][y]=true;
	}
}
void work()
{
	l=0,r=1000.0;
	while(r-l>0.0001)
	{
		mid=0.5*(l+r);
	//	printf("%.4lf %.4lf\n",l,r);
		if(spfa(mid))
			r=mid;
		else l=mid;
	}
	printf("%.2lf\n",l);
}
int main()
{
	init();
	work();
	return 0;
}
