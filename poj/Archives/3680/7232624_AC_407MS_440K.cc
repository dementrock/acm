#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define oo 0x77777777
#define MAXN 500
#define QMAX 500
#define MAXE 2000
struct Edge{
	int v,w,p;
	Edge *next,*pair;
} *edge[MAXN],mempool[MAXE];
struct Pix{
	int x,y,w,id1,id2;
} p[MAXN],pix[MAXN];
int N,K,pn,memnum,tot,S,T,dis[MAXN],
Que[MAXN],Closed,Open,Size,piS,cost,vis[MAXN];
int cmp(const void *a, const void *b){
	Pix *x=(Pix *)a, *y=(Pix *)b;
	return x->x-y->x;
}
inline int min(int a, int b){
	return a<b?a:b;
}
void add(int s, int t, int p, int w){
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->p=p,x->w=w,x->v=t,x->next=edge[s];
	y->p=-p,y->w=0,y->v=s,y->next=edge[t];
	x->pair=y,y->pair=x;
	edge[s]=x,edge[t]=y;
}
void init(){
	scanf("%d %d\n",&N,&K);
	memnum=pn=tot=0;
	memset(edge,0,sizeof(edge));
	for(int i=1;i<=N;++i){
		scanf("%d %d %d\n",&p[i].x,&p[i].y,&p[i].w);
		pix[++pn].x=p[i].x;
		pix[pn].id1=i;
		pix[pn].id2=1;
		pix[++pn].x=p[i].y;
		pix[pn].id1=i;
		pix[pn].id2=2;
	}
	qsort(pix+1,pn,sizeof(pix[0]),cmp);
	for(int i=1;i<=pn;++i){
		if(pix[i].x!=pix[i-1].x) ++tot;
		if(pix[i].id2==1)
			p[pix[i].id1].x=tot;
		else
			p[pix[i].id1].y=tot;
	}
	S=0,T=tot+1;
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
			int d=aug(tmp->v,min(tmpf,tmp->w));
			tmp->w-=d,tmp->pair->w+=d,tmpf-=d;
			if(!tmpf) return minf;
		}
	}
	return minf-tmpf;
}
int modlabel(){
	memset(dis,0x77,sizeof(dis));
	dis[T]=0;
	Closed=0,Open=0,Size=1;
	Que[0]=T;
	while(Size){
		int now=Que[Closed];
		Closed=(Closed+1)%QMAX;
		--Size;
		for(Edge *tmp=edge[now];tmp;tmp=tmp->next){
			if(tmp->pair->w&&(dis[now]-tmp->p)<dis[tmp->v]){
				int pos=Size?Que[Closed]:0;
				dis[tmp->v]=dis[now]-tmp->p;
				++Size;
				if(dis[tmp->v]<=dis[pos]){
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
void work(){
	for(int i=0;i<=tot;++i)
		add(i,i+1,0,K);
	for(int i=1;i<=N;++i)
		add(p[i].x,p[i].y,-p[i].w,1);
	piS=cost=0;
	while(modlabel()){
		do
			memset(vis,0,sizeof(vis));
		while(aug(S,oo));
	}
	printf("%d\n",-cost);
}
int main(){
	int t;
	scanf("%d",&t);
	for(;t--;){
		init();
		work();
	}
	return 0;
}
