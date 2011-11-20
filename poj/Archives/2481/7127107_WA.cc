#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 100030
struct news
{
	int s,e,id;
} cow[MAXN];
int c[MAXN],ans[MAXN],maxx;
inline int max(int a, int b){
	return a>b?a:b;
}
int cmp(const void *a, const void *b){
	news *x=(news *)a, *y=(news *)b;
	if(x->e==y->e)
		return x->s-y->s;
	else
		return y->e-x->e;
}
void add(int x, int d){
	for(;x<=maxx;x+=x&-x)
		c[x]+=d;
}
int getsum(int x){
	int res=0;
	for(;x>0;x-=x&-x)
		res+=c[x];
	return res;
}
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		memset(c,0,sizeof(c));
		for(int i=1;i<=n;++i){
			scanf("%d%d",&cow[i].s,&cow[i].e);
			cow[i].s+=10;
			cow[i].e+=10;
			cow[i].id=i;
			maxx=max(maxx,cow[i].s);
		}
		qsort(cow+1,n,sizeof(cow[0]),cmp);
		for(int i=1;i<=n;++i){
			ans[cow[i].id]=getsum(cow[i].s-1);
			add(cow[i].s,1);
		}
		for(int i=1;i<n;++i)
			printf("%d ",ans[i]);
		printf("%d\n",ans[n]);
	}
	return 0;
}
