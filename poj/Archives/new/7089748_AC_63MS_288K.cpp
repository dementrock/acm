#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1000
#define MAXM 10000
struct Edge
{
	int v,w;
	Edge *next;
} *edge[MAXN+1],mempool[MAXM+1];
int n,m,S,F,memnum,oo,dis[MAXN+1][2],num[MAXN+1][2],ans,vis[MAXN+1][2];
inline int min(int a, int b){return a>b?b:a;}
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
	int a,b,l;
	memnum=0;
	memset(edge,0,sizeof(edge));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&a,&b,&l);
		add(a,b,l);
	}
	scanf("%d%d",&S,&F);
}
void work()
{
	memset(dis,0x77,sizeof(dis));
	memset(&oo,0x77,sizeof(oo));
	memset(vis,0,sizeof(vis));
	dis[S][0]=0;
	for(int i=1;i<=n;++i) num[i][0]=num[i][1]=1;
	for(int i=1;i<=2*n-1;++i)
	{
		int mindis=oo,minj=0,mink=0;
		for(int j=1;j<=n;++j)
			for(int k=0;k<=1;++k)
				if(!vis[j][k])
					if(dis[j][k]<mindis)
					{
						mindis=dis[j][k];
						minj=j;
						mink=k;
					}
		if(mindis>=oo)  break;
		vis[minj][mink]=true;
		for(Edge *tmp=edge[minj];tmp!=NULL;tmp=tmp->next)
		{
			
			int now=mindis+tmp->w;
			if(now<dis[tmp->v][0])
			{
				dis[tmp->v][1]=dis[tmp->v][0];
				dis[tmp->v][0]=now;
				num[tmp->v][1]=num[tmp->v][0];
				num[tmp->v][0]=num[minj][mink];
			}
			else if(now==dis[tmp->v][0])
				num[tmp->v][0]+=num[minj][mink];
			else if(now<dis[tmp->v][1])
			{
				dis[tmp->v][1]=now;
				num[tmp->v][1]=num[minj][mink];
			}
			else if(now==dis[tmp->v][1])
				num[tmp->v][1]+=num[minj][mink];
		}
	}
	ans=num[F][0];
	if(dis[F][1]==dis[F][0]+1) ans+=num[F][1];
	printf("%d\n",ans);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		init();
		work();
	}
	return 0;
}
