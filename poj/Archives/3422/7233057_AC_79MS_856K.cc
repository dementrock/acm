#include<stdio.h>
#include<string.h>
#define MAXN 5100
#define MAXE 100001
#define QMAX 5100
#define oo 0x77777777
struct Edge{
	int v,w,p;
	Edge *next,*pair;
} *edge[MAXN],mempool[MAXE];
int memnum,S,T,N,K,piS,cost,vis[MAXN],
dis[MAXN],Closed,Open,Size,Que[QMAX];
inline int min(int a, int b){
	return a<b?a:b;
}
void add(int s, int t, int p, int w){
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->v=t,x->w=w,x->p=p,x->next=edge[s],edge[s]=x,x->pair=y;
	y->v=s,y->w=0,y->p=-p,y->next=edge[t],edge[t]=y,y->pair=x;
}
int aug(int now, int minf){
	if(now==T){
		cost+=piS*minf;
		return minf;
	}
	vis[now]=1;
	int tmpf=minf;
	for(Edge *tmp=edge[now];tmp;tmp=tmp->next){
		if(tmp->w&&!tmp->p&&!vis[tmp->v]){
			int d=aug(tmp->v,min(minf,tmp->w));
			tmp->w-=d,tmp->pair->w+=d,tmpf-=d;
			if(!tmpf) return minf;
		}
	}
	return minf-tmpf;
}
int modlabel(){
	memset(dis,0x77,sizeof(dis));
	Closed=Open=0,Size=1;
	Que[0]=T;
	dis[T]=0;
	while(Size){
		int now=Que[Closed];
		Closed=(Closed+1)%QMAX,--Size;
		for(Edge *tmp=edge[now];tmp;tmp=tmp->next){
			if(tmp->pair->w&&dis[now]-tmp->p<dis[tmp->v]){
				dis[tmp->v]=dis[now]-tmp->p;
				++Size;
				int pos=Size?dis[Que[Closed]]:oo;
				if(dis[tmp->v]<pos){
					Closed=(Closed-1+QMAX)%QMAX;
					Que[Closed]=tmp->v;
				}else{
					Open=(Open+1)%QMAX;
					Que[Open]=tmp->v;
				}
			}
		}
	}
	for(int i=S;i<=T;++i){
		for(Edge *tmp=edge[i];tmp;tmp=tmp->next){
			tmp->p+=dis[tmp->v]-dis[i];
		}
	}
	piS+=dis[S];
	return dis[S]<oo;
}
int main(){
	scanf("%d %d\n",&N,&K);
	S=0,T=2*N*N+1;
	int x;
	for(int i=1;i<=N;++i){
		for(int j=1;j<=N;++j){
			scanf("%d",&x);
			if(i<N)
				add((i-1+N)*N+j,i*N+j,0,K);
			if(j<N)
				add((i-1+N)*N+j,(i-1)*N+j+1,0,K);
			add((i-1)*N+j,(i-1+N)*N+j,-x,1);
			add((i-1)*N+j,(i-1+N)*N+j,0,K);
		}
	}
	add(S,1,0,K);
	add(2*N*N,T,0,K);
	while(modlabel())
		do
			memset(vis,0,sizeof(vis));
		while(aug(S,oo));
	printf("%d\n",-cost);	
	return 0;
}
