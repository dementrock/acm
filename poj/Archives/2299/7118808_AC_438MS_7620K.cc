#include<stdio.h>
#include<string.h>
struct news
{
	int num,id;
} ta[500001];
int a[500001],c[500001];
long long ans;
void swap(news &a, news &b)
{
	news x=a;
	a=b;
	b=x;
}
void quicksort(news a[], int left, int right)
{
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(a[i],a[right]);
	for(j=left,i=left-1;j<right;++j)
		if(a[j].num<a[right].num)
			swap(a[++i],a[j]);
	swap(a[++i],a[right]);
	quicksort(a,left,i-1);
	quicksort(a,i+1,right);
}
int n;

int init()
{
	scanf("%d",&n);
	if(!n) return 0;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&ta[i].num);
		ta[i].id=i;
	}
}
inline int lowbit(int x)
{
	return x&(-x);
}
void add(int x, int d)
{
	for(;x<=n;x+=lowbit(x))
		c[x]+=d;
}
int getsum(int x)
{
	int res=0;
	for(;x>0;x-=lowbit(x))
		res+=c[x];
	return res;
}
void work()
{
	ans=0;
	memset(c,0,sizeof(c));
	quicksort(ta,1,n);
	ta[0].num=-1;
	int tot=0;
	for(int i=1;i<=n;++i)
		if(ta[i].num==ta[i-1].num)
			a[ta[i].id]=tot;
		else a[ta[i].id]=++tot;
	for(int i=1;i<=n;++i)
	{
		add(a[i],1);
		ans+=i-1-getsum(a[i]-1);
	}
	printf("%I64d\n",ans);
}
int main()
{
	while(1)
	{
		if(!init()) break;
		work();
	}
}
