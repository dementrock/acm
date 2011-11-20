#include<stdio.h>
#include<stdlib.h>
#define MAXN 100001
struct Edge
{
	int v;
	Edge *next;
} *edge[MAXN],mempool[2*MAXN];
int list[MAXN],loc[MAXN],c[MAXN],vis[MAXN],pre[MAXN],lost[MAXN],nlist,n,memnum;
void dfs(int now){
	vis[now]=1;
	if(edge[now]!=NULL)
		if(!vis[edge[now]->v])
			pre[edge[now]->v]=pre[now];
	if(edge[now]->next!=NULL)
		for(Edge *tmp=edge[now];tmp->next!=NULL;tmp=tmp->next)
			if(!vis[tmp->next->v])
				pre[tmp->next->v]=tmp->v;
	for(Edge *tmp=edge[now];tmp!=NULL;tmp=tmp->next) 
		if(!vis[tmp->v])
			dfs(tmp->v);
	list[++nlist]=now;
	loc[now]=nlist;
}
void addedge(int u, int v)
{
	Edge *e=&mempool[memnum++];
	e->v=v;
	e->next=edge[u];
	edge[u]=e;
}
void add(int x, int d)
{
	for(;x<=n;x+=x&(-x))
		c[x]+=d;
}
int getsum(int x)
{
	int res=0;
	for(;x>0;x-=x&(-x))
		res+=c[x];
	return res;
}
int main(){
	int a,b,m,x;
	char c;
	scanf("%d\n",&n);
	for(int i=1;i<=n-1;++i){
		scanf("%d %d\n",&a,&b);
		addedge(a,b);
		addedge(b,a);
	}
	dfs(1);
	scanf("%d\n",&m);
	for(int i=1;i<=n;++i)
		add(i,1);
//	for(int i=1;i<=n;++i)
//		printf("%d %d\n",i,pre[i]);
	for(int i=1;i<=m;++i){
		scanf("%c %d\n",&c,&x);
		if(c=='C'){
			if(!lost[x]) add(loc[x],-1);
			else add(loc[x],1);
			lost[x]=!lost[x];
		}
		else
			printf("%d\n",getsum(loc[x])-getsum(loc[pre[x]]));
	}
	return 0;
}
