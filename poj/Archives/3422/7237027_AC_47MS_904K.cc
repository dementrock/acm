#include<stdio.h>
#include<string.h>
#define MAXN 5100
#define MAXE 100001
#define QMAX 5100
#define oo 0x77777777
struct Edge{
	int v,w,p;
	Edge *next,*pair;
} *edge[MAXN],*tedge[MAXN],mempool[MAXE],*fe[MAXN];
int memnum,S,T,N,K,piS,cost,vis[MAXN],ins[MAXN],ft[MAXN],
dis[MAXN],Closed,Open,Size,Que[QMAX];
inline int min(int a, int b){
	return a<b?a:b;
}
void add(int s, int t, int p, int w){
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->v=t,x->w=w,x->p=p,x->next=edge[s],edge[s]=x,x->pair=y;
	y->v=s,y->w=0,y->p=-p,y->next=edge[t],edge[t]=y,y->pair=x;
}
int spfa(){
	memset(dis,0x77,sizeof(dis));
	memset(ins,0,sizeof(ins));
	memset(ft,0,sizeof(ft));
	memset(fe,0,sizeof(fe));
	Closed=-1,Open=0,Que[0]=S,dis[S]=0,ins[S]=1,Size=1;
	while (Size){
		Closed=(Closed+1)%QMAX;
		int now=Que[Closed];
		ins[now]=0,--Size;
		for(Edge *tmp=edge[now];tmp;tmp=tmp->next){
			int j=tmp->v;
			if(tmp->w&&dis[now]+tmp->p<dis[j])
			{
				dis[j]=dis[now]+tmp->p;
				ft[j]=now;
				fe[j]=tmp;
				if(!ins[j]){
					ins[j]=1;
					++Size;
					Open=(Open+1)%QMAX;
					Que[Open]=j;
				}
			}
		}
	}
	return dis[T]<oo;
}
void aug()
{
	int delta=oo;
	for(int i=T;i!=S;i=ft[i]){
		if(fe[i]->w<delta){
			delta=fe[i]->w;
		}
	}
	for(int i=T;i!=S;i=ft[i]){
		fe[i]->w-=delta;
		fe[i]->pair->w+=delta;
		cost+=fe[i]->p*delta;
	}
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
	piS=cost=0;
	while(spfa()){
		aug();
	}
	printf("%d\n",-cost);	
	return 0;
}
