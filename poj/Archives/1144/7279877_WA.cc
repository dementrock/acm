#include<stdio.h>
#include<string.h>
#define MAXN 101
#define MAXE 20001
struct Edge{
	int v;
	Edge *next;
} *edge[MAXN],mempool[MAXE];
int flag,n,snum,memnum,stack[MAXN],dfn[MAXN],
low[MAXN],vis[MAXN],app[MAXN],ans;
inline int min(int a, int b){
	return a<b?a:b;
}
void add(int u, int v){
	Edge *e=&mempool[memnum++];
	e->v=v,e->next=edge[u],edge[u]=e;
}
int getn(){
	int res=0;char ch;
	for(ch=getchar();'0'<=ch&&ch<='9';ch=getchar())
		res=res*10+ch-'0';
	if(ch=='\n') flag=1;
	return res;
}
void dfs(int now, int f){
	stack[++snum]=now;
	dfn[now]=snum;
	low[now]=dfn[now];
	int c=0;
	for(Edge *i=edge[now];i;i=i->next){
		if(i->v!=f){
			if(vis[i->v]){  //后向边
				low[now]=min(low[now],dfn[i->v]);
			}else{
				++c;
				dfs(i->v,now);
				low[now]=min(low[now],low[i->v]);
				if(f&&low[i->v]>=dfn[now]&&!app[now]){
					++ans;
					app[now]=1;
				}
			}
		}
	}
	if(!f&&c>1&&!app[now]) ++ans;
}
void init(){
	memnum=0;
	ans=0;
	snum=0;
	memset(edge,0,sizeof(edge));
	memset(app,0,sizeof(app));
	memset(vis,0,sizeof(vis));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
}
int main(){
	int now,t;
	while(scanf("%d\n",&n)!=EOF){
		if(!n) break;
		init();
		while(now=getn()){
			if(!now) break;
			flag=0;
			while(t=getn()){
				add(now,t);
				add(t,now);
				if(flag) break;
			}
		}
		dfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
}
