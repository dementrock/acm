#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1000005
int mine,mins,maxe,maxs,a[MAXN],n,k,minque[MAXN],maxque[MAXN];
int cmp1(const void *a, const void *b)
{
	return *(int *)a-*(int *)b;
}
int cmp2(const void *a, const void *b)
{
	return *(int *)b-*(int *)a;
}
void init()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
}
void work()
{
	for(int i=1;i<k;++i)
	{
		while(a[minque[mine]]>a[i]&&mine>=mins) --mine;
		minque[++mine]=i;
	}
	for(int i=k;i<=n;++i)
	{
		while(i-minque[mins]>=k&&mins<=mine) ++mins;
		while(a[minque[mine]]>a[i]&&mine>=mins) --mine;
		minque[++mine]=i;
		printf("%d",a[minque[mins]]);
		if(i<n) printf(" ");
	}
	printf("\n");
	for(int i=1;i<k;++i)
	{
		while(a[maxque[maxe]]<a[i]&&maxe>=maxs) --maxe;
		maxque[++maxe]=i;
	}
	for(int i=k;i<=n;++i)
	{
		while(i-maxque[maxs]>=k&&maxs<=maxe) ++maxs;
		while(a[maxque[maxe]]<a[i]&&maxe>=maxs) --maxe;
		maxque[++maxe]=i;
		printf("%d",a[maxque[maxs]]);
		if(i<n) printf(" ");
	}
	printf("\n");
}
int main()
{
	init();
	work();
	return 0;
}
