#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 20001
#define MAXD 20001
struct forcmp{
	int a,b,id;
} rank[MAXN],trank[MAXN],tmp[MAXN];
int n,a[MAXD+1],c[MAXD+1],r[MAXN],suf[MAXN],height[MAXN];
int K;
void radixsort(forcmp a[], int n){
	memset(c,0,sizeof(c));
	memset(tmp,0,sizeof(tmp));
	for(int i=1;i<=n;++i)
		++c[a[i].b];
	for(int i=1;i<=MAXD;++i)
		c[i]+=c[i-1];
	for(int i=n;i>=1;--i)
		tmp[c[a[i].b]--]=a[i];
	memcpy(a,tmp,sizeof(tmp));
	memset(c,0,sizeof(c));
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
	for(int i=1,j=0,k=0;i<=n;height[r[i++]]=k)
		for(k?--k:k,j=suf[r[i]-1];i+k<=n&&j+k<=n&&a[i+k]==a[j+k];++k);
}
int check(int len){
	int t=0;
	while(t<=n){
		int maxs=0,mins=30001,tmp=t;
		do{
			++t;
		}while(height[t+1]>=len&&t+1<=n);
		if(t-tmp>=K)
			return 1;
	}
	return 0;
}
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		rank[i].a=a[i];
	}
	getsuffix();
	int l=0,r=n/2,m;
	while(l<=r){
		m=l+r>>1;
		if(check(m))
			l=m+1;
		else
			r=m-1;
	}
	while(l&&!check(l)) --l;
	printf("%d\n",l);
	return 0;
}
