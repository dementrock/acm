#include<stdio.h>
#include<string.h>
#define oo 1e9
#define EPS 1e-8
#define MAXN 2001
#define MAXE 20001
struct Edge{
	int v;
	double w;
	Edge *next,*pair;
} *edge[MAXN],mempool[MAXE];
int poor[MAXN][2],found,S,T,N,M,cnt,ecnt,vis[MAXN],tvis[MAXN],memnum,
layer[MAXN],counter[MAXN];
double ans,minf;
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
void createedge(double m){
	memnum=0;
	S=0,T=N+M+1;
	memset(edge,0,sizeof(edge));
	for(int i=1;i<=N;++i){
		add(i,T,m);
	}
	for(int i=1;i<=M;++i){
		add(S,i+N,1);
		add(i+N,poor[i][0],oo);
		add(i+N,poor[i][1],oo);
	}
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
void dfs(int now){
	vis[now]=1;
	for(Edge *tmp=edge[now];tmp;tmp=tmp->next){
		if(!zero(tmp->w)&&tmp->w>0&&!vis[tmp->v]){
			dfs(tmp->v);
		}
	}
}
int main(){
	scanf("%d %d\n",&N,&M);
	if(!M){
		printf("1\n1\n");
		return 0;
	}
	for(int i=1;i<=M;++i){
		scanf("%d %d\n",&poor[i][0],&poor[i][1]);
	}
	double l=1.0/N,r=M,m;
	while(r-l>=EPS){
		m=(l+r)*0.5;
		createedge(m);
		sap();
		ans=M-ans;
		if(zero(ans)){
			r=m;
		}else{
			memcpy(tvis,vis,sizeof(tvis));
			memset(vis,0,sizeof(vis));
			dfs(S);
			int tecnt=ecnt;
			ecnt=0;
			for(int i=N+1;i<=N+M;++i){
				if(vis[i]){
					++ecnt;
					vis[poor[i-N][0]]=1;
					vis[poor[i-N][1]]=1;
				}
			}
			int tcnt=cnt;cnt=0;
			for(int i=1;i<=N;++i)
				if(vis[i])
					++cnt;
			if(!cnt||!ecnt||tcnt&&ecnt*1.0/cnt<tecnt*1.0/tcnt){
				memcpy(vis,tvis,sizeof(tvis));
				cnt=tcnt;
				ecnt=tecnt;
			}
			if(ans>0){
				l=m;
			}else{
				r=m;
			}
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=N;++i){
		if(vis[i]){
			printf("%d\n",i);
		}
	}
	return 0;
}
