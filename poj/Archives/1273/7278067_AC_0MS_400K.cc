#include<stdio.h>
#include<string.h>
#define MAXN 1001
#define MAXE 1001
#define oo 0x77777777
struct Edge{
	int v,w;
	Edge *next,*pair;
} *edge[MAXN],mempool[MAXE];
int N,M,S,T,counter[MAXN],
ans,minf,found,memnum,layer[MAXN];
inline int min(int a, int b){
	return a<b?a:b;
}
void add(int s, int t, int w){
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->v=t,x->w=w,x->next=edge[s],x->pair=y,edge[s]=x;
	y->v=s,y->w=0,y->next=edge[t],y->pair=x,edge[t]=y;
}
void aug(int now){
	if(now==T){
		found=1;
		ans+=minf;
		return;
	}
	int tmp=minf,minl=T-1;
	Edge *i;
	for(i=edge[now];i;i=i->next){
		if(i->w>0){
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
	counter[0]=T;
	ans=0;
	for(;layer[S]<T;){
		found=0;
		minf=oo;
		aug(S);
	}
}
int main(){
	int a,b,c;
	while(scanf("%d %d\n",&M,&N)!=EOF){
		S=1,T=N;
		memnum=0;
		memset(edge,0,sizeof(edge));
		for(int i=1;i<=M;++i){
			scanf("%d %d %d\n",&a,&b,&c);
			add(a,b,c);
		}
		sap();
		printf("%d\n",ans);
	}
	return 0;
}
