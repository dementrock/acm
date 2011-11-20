#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 20010
#define MAXM 200010
struct Edge
{
	int v,w;
	Edge *next;
} *tv[MAXN],*v[MAXN],mempool[6*MAXM+1];
int n,m,s,t,found,minf,oo=999999999,ans,memnum,layer[MAXN],counter[MAXN],vis[MAXN];
inline int min(int a, int b){return a>b?b:a;}
void add1(int x, int y, int z)
{
	Edge *e=&mempool[++memnum];
	e->v=y;
	e->w=z;
	e->next=tv[x];
	tv[x]=e;
}
void add2(int x, int y, int z)
{
	Edge *e=&mempool[++memnum];
	e->v=y;
	e->w=z;
	e->next=v[x];
	v[x]=e;
}
void init()
{
	int x,y,z;
	scanf("%d%d",&n,&m);
	s=0,t=n+1;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&x,&y);
		add1(s,i,x);
		add1(i,t,y);
		add2(s,i,x);
		add2(i,t,y);
		add2(i,s,0);
		add2(t,i,0);
	}
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		add1(x,y,z);
		add1(y,x,z);
		add2(x,y,z);
		add2(y,x,z);
	}
}
void aug(int now)
{
//	printf("flow:%d\n",now);
	int i,tmpf=minf,minl=t-1;
	if(now==t)
	{
		found=1;
		return;
	}
	for(Edge *tmp=v[now];tmp!=NULL;tmp=tmp->next)
	if(tmp->w>0)
	{
		
		if(layer[now]==layer[tmp->v]+1)
		{
			minf=min(minf,tmp->w);
			aug(tmp->v);
			if(found)
			{
				i=tmp->v;
				break;
			}
			if(layer[s]>=t) return;
			minf=tmpf;
		}
		minl=min(minl,layer[now]);
	}
	if(!found)
	{
		
	//	printf("y");
		--counter[layer[now]];
		if(!counter[layer[now]]) layer[s]=t;
		layer[now]=minl+1;
		++counter[layer[now]];
	}
	else
	{
	//	printf("y");
		for(Edge *tmp=v[now];tmp!=NULL;tmp=tmp->next)
			if(tmp->v==i)
			{
				tmp->w-=minf;
		//		printf("y");
				break;
			}
		for(Edge *tmp=v[i];tmp!=NULL;tmp=tmp->next)
			if(tmp->v==now)
			{
				tmp->w+=minf;
				break;
			}
	}
}
void sap()
{
	counter[0]=t+1;
	while(layer[s]<t)
	{
		found=0;
		minf=oo;
		aug(s);
	}
}
void dfs(int now)
{
	vis[now]=1;
	for(Edge *tmp=v[now];tmp!=NULL;tmp=tmp->next)
		if(tmp->w&&!vis[tmp->v])
			dfs(tmp->v);
}
void work()
{
	sap();
//	while(1);
	dfs(s);
//	for(int i=s;i<=t;++i) printf("%d ",vis[i]);
//	printf("\n");
	for(int i=s;i<=t;++i)
		for(Edge *tmp=tv[i];tmp!=NULL;tmp=tmp->next)
			if(vis[i]&&!vis[tmp->v])
				ans+=tmp->w;
	printf("%d\n",ans);
}
int main()
{
	init();
	work();
	return 0;
}
