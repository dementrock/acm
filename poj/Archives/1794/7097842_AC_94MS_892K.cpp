#include<stdio.h>
#include<string.h>
#define MAXN 70000
int a[MAXN],b[MAXN],c[MAXN],ans,n,m;
void swap(int &a, int &b){int x=a;a=b;b=x;}
void quicksort(int left, int right)
{
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(a[i],a[right]);
	swap(b[i],b[right]);
	for(j=left,i=left-1;j<right;++j)
		if(a[j]<a[right])
		{
			swap(a[++i],a[j]);
			swap(b[i],b[j]);
		}
	swap(a[++i],a[right]);
	swap(b[i],b[right]);
	quicksort(left,i-1);
	quicksort(i+1,right);
}
inline int lowbit(int x){return x&(-x);}
int sum(int x)
{
	int ret=0;
	for(int t=x;t>=1;t-=lowbit(t))
		if(t) ret+=c[t];
	return ret;
}
void add(int x, int d)
{
	for(int t=x;t<=n+m;t+=lowbit(t))
		c[t]+=d;
}
int main()
{
	int t,counter=0;
	scanf("%d",&t);
	for(counter=1;counter<=t;++counter)
	{
		ans=0;
		memset(c,0,sizeof(c));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n+m;++i)
			scanf("%d%d",&a[i],&b[i]);
		quicksort(1,n+m);
		for(int i=1;i<=n+m;++i)
		{
			ans+=i-sum(b[i]-1)-1;
			add(b[i],1);
		}
		printf("Scenario #%d:\n%d\n\n",counter,ans);
	}
}
