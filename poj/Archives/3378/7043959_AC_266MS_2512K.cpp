#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct news
{
	int id,num;
} ta[50001];
__int64 a[50001],b[50001],c[50001],d[50001],e[50001],n,ans[10],data[50001];
void swap(news &a, news &b)
{
	news x=a;a=b;b=x;
}
int partition(news a[], int left, int right)
{
	int i=left+right>>1,j;
	swap(a[i],a[right]);
	for(j=left,i=left-1;j<right;++j)
		if(a[j].num<a[right].num)
			swap(a[++i],a[j]);
	swap(a[++i],a[right]);
	return i;
}
void quicksort(news a[], int left, int right)
{
	if(left>=right) return;
	int i=partition(a,left,right);
	quicksort(a,left,i-1);
	quicksort(a,i+1,right);
}
int lowbit(int k)
{
	return k&(-k);
}
long long sum(int k)
{
	long long ans=0,t=k;
	while(t>0)
	{
		ans+=data[t];
		t-=lowbit(t);
	}
	return ans;
}
void change(int id, __int64 k)
{
	int t=id;
	while(t<=n)
	{
		data[t]+=k;
		t+=lowbit(t);
	}
}
void init()
{
	int t=1;
	if(scanf("%d\n",&n)==EOF) exit(0);
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	memset(d,0,sizeof(d));
	memset(ans,0,sizeof(ans));
	memset(ta,0,sizeof(ta));
	memset(data,0,sizeof(data));
	for(int i=1;i<=n;++i)
	{
		ta[i].id=i;
		scanf("%d",&ta[i].num);
	}
	quicksort(ta,1,n);
	for(int i=1;i<=n;++i)
	{
		a[ta[i].id]=t;
		if(t==n||ta[i].num!=ta[i+1].num) ++t;
	}
}
void work()
{
	for(int i=1;i<=n;++i)
	{
		change(a[i],1);
		b[i]=sum(a[i]-1);
	}
	memset(data,0,sizeof(data));
	for(int i=1;i<=n;++i)
	{
		change(a[i],b[i]);
		c[i]=sum(a[i]-1);
	}
	memset(data,0,sizeof(data));
	for(int i=1;i<=n;++i)
	{
		change(a[i],c[i]);
		d[i]=sum(a[i]-1);
	}
	memset(data,0,sizeof(data));
	for(int i=1;i<=n;++i)
	{
		change(a[i],d[i]);
		ans[0]+=sum(a[i]-1);
		for(int i=1;i<=9;++i)
		{
			ans[i]+=ans[i-1]/10000000;
			ans[i-1]%=10000000;
		}
	}
}
void print()
{
	int i;
	for(i=9;i>=0;--i) if(ans[i]!=0) break;
	printf("%I64d",ans[i]);
	for(--i;i>=0;--i)
	{
		if(ans[i]<1000000)
			printf("0");
		if(ans[i]<100000)
			printf("0");
		if(ans[i]<10000)
			printf("0");
		if(ans[i]<1000)
			printf("0");
		if(ans[i]<100)
			printf("0");
		if(ans[i]<10)
			printf("0");
		printf("%I64d",ans[i]);
	}
	printf("\n");
}
int main()
{
	while(1){
	init();
	work();
	print();}
	return 0;
}
