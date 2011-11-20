#include<stdio.h>
#include<string.h>
#define MAXN 5100
#define MAXE 100001
#define oo 9223372036854775807LL
struct Edge{
	int v;
	long long w;
	Edge *next,*pair;
} *edge[MAXN],mempool[MAXE];
long long b[MAXN],ans,minf,sum;
int S,T,found,memnum,layer[MAXN],counter[MAXN];
inline long long min(long long a, long long b){
	return a<b?a:b;
}
inline int min(int a, int b){
	return a<b?a:b;
}
void add(int s, int t, long long w){
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->v=t,x->pair=y,x->w=w,x->next=edge[s],edge[s]=x;
	y->v=s,y->pair=x,y->w=0,y->next=edge[t],edge[t]=y;
}
void aug(int now){
	if(now==T){
		ans+=minf;
		found=1;
		return;
	}
	Edge *i;
	int minl=T-1;
	long long tmp=minf;
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
	counter[0]=T+1;
	while(layer[S]<T){
		found=0;
		minf=oo;
		aug(S);
	}
}
int main(){
	int n,m,x,y,s=0;
	scanf("%d %d\n",&n,&m);
	S=0,T=n+1;
	for(int i=1;i<=n;++i){
		scanf("%I64d",&b[i]);
		b[i]=b[i]*10000-1;
		if(b[i]>0){
			add(S,i,b[i]);
			++s;
			sum+=b[i]+1;
		}else
			add(i,T,-b[i]);
	}
	for(int i=1;i<=m;++i){
		scanf("%d %d",&x,&y);
		add(x,y,oo);
	}
	sap();
	printf("%I64d %I64d\n",ans,(ans+s)%10000,(sum-ans)/10000);
	return 0;
}
