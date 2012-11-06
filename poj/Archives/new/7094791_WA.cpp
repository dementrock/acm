#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1001
#define MAXM 100001
#define MAXH 1000001
struct Edge
{
	int v,w;
	Edge *next;
} *edge[MAXN],*edge2[MAXN],mempool[MAXM+1];
int h[MAXH],id[MAXH],dis[MAXN],que[MAXN],vis[MAXN],size,memnum,Closed,Open,n,m,S,T,K,c[MAXN];
void swap(int &a, int &b){int x=a;a=b;b=x;}
void add(int u, int v, int w)
{
	Edge *e=&mempool[++memnum];
	e->v=v;
	e->w=w;
	e->next=edge[u];
	edge[u]=e;
}
void add2(int u, int v, int w)
{
	Edge *e=&mempool[++memnum];
	e->v=v;
	e->w=w;
	e->next=edge2[u];
	edge2[u]=e;
}
void heapdown(int now)
{
	int t=now;
	while(1)
	{
		int l=t<<1,r=(t<<1)+1,heapmax=t;
		if(l<=size&&h[l]<h[heapmax]) heapmax=l;
		if(r<=size&&h[r]<h[heapmax]) heapmax=r;
		if(heapmax==t) return;
		swap(h[heapmax],h[t]);
		swap(id[heapmax],id[t]);
		t=heapmax;
	}
}
void heapup(int now)
{
	int t=now;
	while(t>1&&h[t]<h[t>>1])
	{
		swap(h[t],h[t>>1]);
		swap(id[t],id[t>>1]);
		t>>=1;
	}
}
void insert(int key, int ID)
{
	h[++size]=key;
	id[size]=ID;
	heapup(size);
}
void extmin()
{
	id[1]=id[size];
	h[1]=h[size--];
	heapdown(1);
}
void spfa(int s)
{
	memset(dis,0x77,sizeof(dis));
	dis[s]=0;
	que[0]=s;
	vis[s]=true;
	Closed=-1,Open=0;
	while(Closed!=Open)
	{
		Closed=(Closed+1)%n;
		int now=que[Closed];
	//	printf("%d\n",now);
		for(Edge *tmp=edge2[now];tmp!=NULL;tmp=tmp->next)
		{
	//		printf("y");
			if(dis[now]+tmp->w<dis[tmp->v])
			{
				dis[tmp->v]=dis[now]+tmp->w;
				if(!vis[tmp->v])
				{
					vis[tmp->v]=true;
					Open=(Open+1)%n;
					que[Open]=tmp->v;
				}
			}
		}
		vis[now]=false;
	}
//	for(int i=1;i<=n;++i) printf("%d\n",dis[i]);
}
int astar()
{
//	printf("%d\n",1);
	insert(dis[S],S);
	while(size)
	{
	//	printf("%d\n",size);
		int th=h[1],tid=id[1];
		extmin();
		
		++c[tid];
		if(c[T]==K) return th;
		if(c[tid]>K) continue;
		for(Edge *tmp=edge[tid];tmp!=NULL;tmp=tmp->next)
			insert(th-dis[tid]+dis[tmp->v]+tmp->w,tmp->v);
	}
	return -1;
}
void init()
{
	int a,b,t;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&a,&b,&t);
		add(a,b,t);
		add2(b,a,t);
	}
	scanf("%d%d%d",&S,&T,&K);
}
void work()
{
	spfa(T);
	printf("%d\n",astar());
}
int main()
{
	init();
	work();
	return 0;
}
