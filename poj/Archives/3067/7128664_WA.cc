#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct news{
	int x,y;
} a[1000001];
int t,n,m,k,ans,c[1001];
int cmp(const void *a, const void *b){
	news *x=(news*)a, *y=(news*)b;
	if(x->x==y->x)
		return y->y-x->y;
	else
		return y->x-x->x;
}
void add(int x, int d){
	for(;x<=m;x+=x&-x)
		c[x]+=d;
}
int getsum(int x){
	int res=0;
	for(;x>0;x-=x&-x)
		res+=c[x];
}
int main()
{
	scanf("%d",&t);
	for(int times=1;times<=t;++times){
		scanf("%d%d%d",&n,&m,&k);
		memset(c,0,sizeof(c));
		ans=0;
		for(int i=1;i<=k;++i)
			scanf("%d%d",&a[i].x,&a[i].y);
		qsort(a+1,k,sizeof(a[0]),cmp);
		for(int i=1;i<=k;++i){
			ans+=getsum(a[i].y);
			add(a[i].y,1);
		}
		printf("Test case %d: %d\n",times,ans);
	}
}
