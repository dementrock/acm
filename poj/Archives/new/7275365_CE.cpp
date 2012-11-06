#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAXN 100001
#define MAXE 200001
struct Edge{
	int v,w;
	Edge *next;
} *edge[MAXN], mempool[MAXE];
int memnum, road[MAXE][3], dep[MAXN], vis[MAXN], tapp[MAXN], 
stack[MAXN], app[MAXN], snum, tnum, n, q, cur, tree[MAXN], 
son[MAXN], cnum[MAXN], st[2*MAXN][20];
inline int rmin(int a, int b){
	return dep[a]<dep[b]?a:b;
}
void add(int u, int v, int w){
	Edge *e=&mempool[memnum++];
	e->v=v,e->w=w,e->next=edge[u],edge[u]=e;
}
int getn(){
	char ch;
	int res=0;
	for(ch=getchar();'0'<=ch&&ch<='9';ch=getchar())
		res=res*10+ch-'0';
	return res;
}
void predfs(int now, int deep){
	dep[now]=deep;
	vis[now]=1;
	stack[++snum]=now;
	tree[++tnum]=now;
	tapp[now]=tnum;
	if(!app[now]) app[now]=snum;
	for(Edge *tmp=edge[now];tmp;tmp=tmp->next){
		if(!vis[tmp->v]){
			predfs(tmp->v,deep+1);
			stack[++snum]=now;
			son[now]+=son[tmp->v]+1;
		}
	}
}
void find(int i, int k){
	if(k==1){
		st[i][k]=stack[i];
		return;
	}
	if(!st[i][k-1]) find(i,k-1);
	if(!st[i+(1<<(k-1))][k-1]) find(i+(1<<(k-1)),k-1);
	st[i][k]=rmin(st[i][k-1],st[i+(1<<(k-1))][k-1]);
}
int rmq(int l, int r){
	int k=int(log(r-l+1)/log(2));
	if(!st[l][k]) find(l,k);
	if(!st[r-(1<<k)+1][k]) find(r-(1<<k)+1,k);
	return rmin(st[l][k], st[r-(1<<k)+1][k]);
}
int getsum(int x){
	int res=0;
	for(;x>0;x-=x&-x)
		res+=cnum[x];
	return res;
}
void add(int x, int d){
	for(;x<=n;x+=x&-x)
		cnum[x]+=d;
}
int lca(int a, int b){
	int x=app[a], y=app[b];
	if(x<y) return rmq(x,y);
	else return rmq(y,x);
}
int dist(int now){
	return getsum(tapp[now]);
}
int ask(int a, int b){
	return dist(a)+dist(b)-2*dist(lca(a,b));
}
void change(int i, int w){
	int a=road[i][0], b=road[i][1];
	if(dep[a]>dep[b]){ int tmp=a;a=b;b=tmp;}
	add(tapp[b], w-road[i][2]);
	add(tapp[b]+son[b]+1, road[i][2]-w);
	road[i][2]=w;
}
int main(){
	int u,a,b,w,c;
	scanf("%d %d %d\n",&n,&q,&cur);
	for(int i=1;i<n;++i){
		a=getn(), b=getn(), w=getn();
		add(a,b,w);
		add(b,a,w);
		road[i][0]=a;
		road[i][1]=b;
		road[i][2]=w;
	}
	predfs(1,0);
	for(int i=1;i<n;++i){
		w=road[i][2];
		road[i][2]=0;
		change(i,w);
	}
	for(int i=1;i<=q;++i){
		c=getn();
		if(!c){
			u=getn();
			printf("%d\n",ask(cur,u));
			cur=u;
		}else{
			a=getn(), b=getn();
			change(a,b);
			road[a][2]=b;
		}
	}
	return 0;
}
