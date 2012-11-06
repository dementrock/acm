#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1000
#define MAXM 5000
struct Edge
{
	int x,y;
	double z;
} edge[MAXM+1];
int vis[MAXN+1],que[MAXN+1],c[MAXN+1],
map[MAXN+1][MAXN+1],
closed,Open,m,n;
double dis[MAXN+1],v[MAXN+1][MAXN+1],f[MAXN+1],l,r,mid,oo=1999999999;
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
		
		for(int i=1;i<=n;++i) if(map[now][i])
			if(dis[now]+v[now][i]*mid-f[now]<dis[i])
			{
				dis[i]=dis[now]+v[now][i]*mid-f[now];
			//	printf("%d %.3lf\n",i,dis[i]);
				if(!vis[i])
				{
					Open=(Open+1)%n;
					vis[i]=true;
					que[Open]=i;
					++c[i];
					if(c[i]>n) return 0;
				}
			}
		vis[now]=false;
	}
	return 1;
}
void init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lf",&f[i]);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%lf",&edge[i].x,&edge[i].y,&edge[i].z);
		v[edge[i].x][edge[i].y]=edge[i].z;
		map[edge[i].x][edge[i].y]=true;
	}
}
void work()
{
	l=0,r=1000000.0;
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
