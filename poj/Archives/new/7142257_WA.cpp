/*
ID: dementr1
PROG: theme
LANG: C++
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 30001
#define MAXD 30001
struct forcmp{
	int a,b,id;
} rank[MAXN],trank[MAXN],tmp[MAXN];
int n,a[MAXN],c[MAXD+1],tc[MAXD+1],r[MAXN],suf[MAXN],height[MAXN];
inline int max(int a, int b){return a>b?a:b;}
inline int min(int a, int b){return a<b?a:b;}
int cmp(const void *a, const void *b){
	forcmp *x=(forcmp*)a, *y=(forcmp*)b;
	if(x->a==y->a)
		return x->b-y->b;
	else
		return x->a-y->a;
}
void radixsort(forcmp a[], int n){
	memset(c,0,sizeof(c));
	memset(tc,0,sizeof(tc));
	memset(tmp,0,sizeof(tmp));
	for(int i=1;i<=n;++i)
		++c[a[i].b];
	for(int i=1;i<=MAXD;++i)
		c[i]+=c[i-1];
	for(int i=n;i>=1;--i)
		tmp[c[a[i].b]--]=a[i];
	memcpy(a,tmp,sizeof(tmp));
	memset(c,0,sizeof(c));
	memset(tc,0,sizeof(tc));
	memset(tmp,0,sizeof(tmp));
	for(int i=1;i<=n;++i)
		++c[a[i].a];
	for(int i=1;i<=MAXD;++i)
		c[i]+=c[i-1];
	for(int i=n;i>=1;--i)
		tmp[c[a[i].a]--]=a[i];
	memcpy(a,tmp,sizeof(tmp));
}
void getsuffix(){
	for(int i=n;i>=1;--i)
		rank[i].a=a[i]=a[i]-a[i-1]+100;
	for(int k=0;k+1<=n;k=k?k<<1:1){
		memcpy(trank,rank,sizeof(rank));
		for(int i=1;i<=n;++i){
			trank[i].b=i+k<=n?rank[i+k].a:0;
			trank[i].id=i;
		}
		radixsort(trank,n);
		int tot=0;
		for(int i=1;i<=n;++i){
			if(trank[i].a==trank[i-1].a&&trank[i].b==trank[i-1].b)
				rank[trank[i].id].a=rank[trank[i-1].id].a;
			else
				rank[trank[i].id].a=++tot;
		}
	}
	for(int i=1;i<=n;++i)
		r[i]=rank[i].a,suf[r[i]]=i;
}
int check(int len){
	int t=0;
//	printf("%d\n",len);
	while(t<=n){
		int maxs=0,mins=9999;
	//	printf("%d ",t);
		do{
			++t;
			maxs=max(maxs,suf[t]);
			mins=min(mins,suf[t]);
		}while(height[t+1]>=len&&t+1<=n);
	//	printf("%d\n",t);
		if(maxs-mins>len) return 1;
	}
	return 0;
}
void work(){
//	for(int i=1;i<=n;++i)
//		printf("%d ",suf[i]);
//	printf("\n");
	for(int i=1,j=0,k=0;i<=n;height[r[i++]]=k)
		for(k?--k:k,j=suf[r[i]-1];a[i+k]==a[j+k];++k);
//	for(int i=1;i<=n;++i)
//		printf("%d ",height[i]);
//	printf("\n");
	int l=0,r=n/2+1,m;
	while(l<=r){
		m=l+r>>1;
		if(check(m))
			l=m+1;
		else
			r=m-1;
	}
//	printf("%d\n",check(4));
	if(!check(l)) --l;
	printf("%d\n",l>=5?l:0);
}
int main(){
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		getsuffix();
		work();
	}
	return 0;
}
		
