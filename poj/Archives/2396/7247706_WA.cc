#include<stdio.h>
#include<string.h>
#define MAXN 401
#define MAXE 100001
struct Edge{
	int v,w,initw;
	Edge *next,*pair;
} *edge[MAXN],mempool[MAXE];
int M[MAXN],colsum[MAXN],minf,oo=0x77777777,
found,S,T,tS,tT,memnum,layer[MAXN],counter[MAXN],
m,n,rowsum[MAXN],lb[MAXN][MAXN],ansf,
ub[MAXN][MAXN],ans[MAXN][MAXN];
inline int min(int a, int b){
	return a<b?a:b;
}
inline int max(int a, int b){
	return a>b?a:b;
}
void add(int s, int t, int nlb, int nub){
//	printf("%d %d %d %d\n",s,t,nlb,nub);
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->v=t,x->pair=y,x->w=nub-nlb,x->initw=1,x->next=edge[s],edge[s]=x;
	y->v=s,y->pair=x,y->w=0,y->initw=0,y->next=edge[t],edge[t]=y;	
	M[t]+=nlb;
	M[s]-=nlb;
}
void add(int s, int t, int w){
	Edge *x=&mempool[memnum++],*y=&mempool[memnum++];
	x->v=t,x->pair=y,x->w=w,x->initw=1,x->next=edge[s],edge[s]=x;
	y->v=s,y->pair=x,y->w=0,y->initw=0,y->next=edge[t],edge[t]=y;	
}
void aug(int now){
	if(now==T){
		ansf+=minf;
		found=1;
		return;
	}
	Edge *i;
	int tmp=minf,minl=T-1;
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
	counter[0]=T+1;
	while(layer[S]<T){
		found=0;
		minf=oo;
		aug(S);
	}
}
int init(){
	scanf("%d %d\n",&m,&n);
	memset(lb,0,sizeof(lb));
	memset(ub,0x77,sizeof(ub));
	for(int i=1;i<=m;++i){
		scanf("%d",&rowsum[i]);
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&colsum[i]);
	}
	char c1;
	int x1,x2,x3,c;
	scanf("%d\n",&c);
	for(int i=1;i<=c;++i){
		scanf("%d %d %c %d\n",&x1,&x2,&c1,&x3);
		if(x1&&x2){
			if(c1=='>'){
				lb[x1][x2]=max(lb[x1][x2],x3+1);
			}else if(c1=='='){
				lb[x1][x2]=max(lb[x1][x2],x3);
				ub[x1][x2]=min(ub[x1][x2],x3);
			}else{
				ub[x1][x2]=min(ub[x1][x2],x3-1);
			}
		}else if(x1){
			for(x2=1;x2<=n;++x2){
				if(c1=='>'){
					lb[x1][x2]=max(lb[x1][x2],x3+1);
				}else if(c1=='='){
					lb[x1][x2]=max(lb[x1][x2],x3);
					ub[x1][x2]=min(ub[x1][x2],x3);
				}else{
					ub[x1][x2]=min(ub[x1][x2],x3-1);
				}
			}
		}else if(x2){
			for(x1=1;x1<=m;++x1){
				if(c1=='>'){
					lb[x1][x2]=max(lb[x1][x2],x3+1);
				}else if(c1=='='){
					lb[x1][x2]=max(lb[x1][x2],x3);
					ub[x1][x2]=min(ub[x1][x2],x3);
				}else{
					ub[x1][x2]=min(ub[x1][x2],x3-1);
				}
			}
		}else{
			for(x1=1;x1<=m;++x1){
				for(x2=1;x2<=n;++x2){
					if(c1=='>'){
						lb[x1][x2]=max(lb[x1][x2],x3+1);
					}else if(c1=='='){
						lb[x1][x2]=max(lb[x1][x2],x3);
						ub[x1][x2]=min(ub[x1][x2],x3);
					}else{
						ub[x1][x2]=min(ub[x1][x2],x3-1);
					}
				}
			}
		}
	}
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j){
			if(ub[i][j]<lb[i][j]){
				return 0;
			}
		}
	}
	return 1;
}
int work(){
	S=0,T=n+m+3,tS=1,tT=n+m+2;
	for(int i=1;i<=m;++i)
		add(tS,i+1,rowsum[i],rowsum[i]);
	for(int i=1;i<=n;++i)
		add(i+m+1,tT,colsum[i],colsum[i]);
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)
			add(i+1,j+m+1,lb[i][j],ub[i][j]);
	add(tT,tS,0,oo);
	for(int i=tS;i<=tT;++i){
//		printf("%d %d\n",i,M[i]);
		if(M[i]>=0)
			add(S,i,M[i]);
		else
			add(i,T,-M[i]);
	}
	sap();
//	printf("%d\n",ansf);
//	while(1);
	for(Edge *tmp=edge[S];tmp;tmp=tmp->next){
		if(tmp->initw&&tmp->w){
			return 0;
		}
	}
	for(int i=1;i<=m;++i){
		for(Edge *tmp=edge[i+1];tmp;tmp=tmp->next){
			if(tmp->initw){
				ans[i][tmp->v-m-1]=ub[i][tmp->v-m-1]-tmp->w;
			}
		}
	}
}
void print(){
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j){
			printf("%d%c",ans[i][j],j<n?' ':'\n');
		}
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		if(!init()||!work()){
			printf("IMPOSSIBLE\n");
		}else
			print();
		printf("\n");
	}
	return 0;
}
