#include<stdio.h>
#define MAXN 20010
long long v[MAXN],x[MAXN],c1[MAXN],c2[MAXN],ans;
int n;
inline long long lowbit(int x){return x&(-x);}
void swap(long long &a, long long &b){long long x=a;a=b;b=x;}
void quicksort(int left, int right)
{
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(v[i],v[right]);
	swap(x[i],x[right]);
	for(j=left,i=left-1;j<right;++j)
		if(v[j]<v[right])
		{
			swap(v[++i],v[j]);
			swap(x[i],x[j]);
		}
	swap(v[++i],v[right]);
	swap(x[i],x[right]);
	quicksort(left,i-1);
	quicksort(i+1,right);
}
void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%I64d%I64d",&v[i],&x[i]);
	quicksort(1,n);
}
void add(long long c[MAXN], long long x, long long d)
{
//	if(x>n||x<1) return;
	for(long long t=x;t<=MAXN;t+=lowbit(t))
		c[t]+=d;
}
long long getsum(long long c[MAXN], long long x)
{
	long long sum=0;
//	if(x>n||x<1) return sum;
	for(long long t=x;t>=1;t-=lowbit(t))
		sum+=c[t];
	return sum;
}
void work()
{
	for(int i=1;i<=n;++i)
	{
		long long co=getsum(c1,x[i]),num=getsum(c2,x[i]),tot=getsum(c1,MAXN);
		ans+=v[i]*(x[i]*num-co+tot-co-x[i]*(i-1-num));
		add(c1,x[i],x[i]);
		add(c2,x[i],1);
	}
	printf("%I64d\n",ans);
}
int main()
{
	init();
	work();
	return 0;
}
