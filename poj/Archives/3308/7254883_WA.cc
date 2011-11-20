#include<stdio.h>
#include<string.h>
#include<cmath>
#define MAXN 501
#define MAXE 10001
#define oo 1e6
#define EPS 1e-16
struct Edge{
	int v;
	double w;
	Edge *next,*pair;
} *edge[MAXN],mempool[MAXE];
int M,N,L,S,T,found,layer[MAXN],counter[MAXN],memnum,
vis[MAXN],final[MAXN],has[MAXN][MAXN];
double ans,minf,row[MAXN],column[MAXN];
inline double min(double a, double b){
	return a<b?a:b;
}
inline double abs(double x){
	return x>=0?x:-x;
}
inline double zero(double x){
	return abs(x)<EPS;
}
inline int min(int a, int b){
	return a<b?a:b;
}
void add(int s, int t, double w){
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->v=t,x->w=w,x->pair=y,x->next=edge[s],edge[s]=x;
	y->v=s,y->w=0,y->pair=x,y->next=edge[t],edge[t]=y;
}
void aug(int now){
	if(now==T){
		ans+=minf;
		found=1;
		return;
	}
	Edge *i;
	double tmp=minf;
	int minl=T-1;
	for(i=edge[now];i;i=i->next){
		if(!zero(i->w)&&i->w>0){
			if(layer[now]==layer[i->v]+1){
				minf=min(minf,i->w);
				aug(i->v);
				if(layer[S]>=T) return;
				if(found) break;
				minf=tmp;
			}
			minl=min(minl,layer[i->v]);
		}
	}
	if(!found){
		if(!(--counter[layer[now]])) layer[S]=T;
		++counter[layer[now]=minl+1];
	}else{
		i->w-=minf;
		i->pair->w+=minf;
	}
}
void sap(){
	memset(layer,0,sizeof(layer));
	memset(counter,0,sizeof(counter));
	counter[0]=T+1;
	ans=0;
	while(layer[S]<T){
		found=0;
		minf=oo;
		aug(S);
	}
}
void init(){
	int a,b;
	double x,tmp;
	memnum=0;
	memset(edge,0,sizeof(edge));
	memset(has,0,sizeof(has));
	scanf("%d %d %d\n",&M,&N,&L);
	S=0,T=M+N+1;
	for(int i=1;i<=M;++i){
		scanf("%lf",&x);
		row[i]=x;
		tmp=log(x);
		if(!zero(tmp)){
			add(S,i,tmp);
		}
	}
	for(int i=1;i<=N;++i){
		scanf("%lf",&x);
		column[i]=x;
		tmp=log(x);
		if(!zero(tmp)){
			add(i+M,T,tmp);
		}
	}
	for(int i=1;i<=L;++i){
		scanf("%d %d\n",&a,&b);
		if(has[a][b]) continue;
		has[a][b]=1;
		add(a,b+M,oo);
	}
}
void dfs(int now){
	vis[now]=1;
	for(Edge *tmp=edge[now];tmp;tmp=tmp->next){
		if(!zero(tmp->w)&&tmp->w>0){
			if(!vis[tmp->v]){
				dfs(tmp->v);
			}
		}
	}
}
void work(){
	sap();
	memset(vis,0,sizeof(vis));
	memset(final,0,sizeof(final));
	dfs(S);
	for(int i=S;i<=T;++i){
		for(Edge *tmp=edge[i];tmp;tmp=tmp->next){
			if(!zero(tmp->w)&&tmp->w>0){
				if(!vis[i]&&vis[tmp->v]){
					final[i]=final[tmp->v]=1;
				}
			}
		}
	}
	ans=1.0;
	for(int i=1;i<=M;++i){
		if(final[i]) ans*=row[i];
	}
	for(int i=1;i<=N;++i){
		if(final[i+M]) ans*=column[i];
	}
	printf("%.4lf\n",ans);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		init();
		work();
	}
	return 0;
}
