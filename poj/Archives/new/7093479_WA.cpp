#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 90001
int n,a[MAXN],steak[MAXN],top,c[MAXN];
long long ans;
void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
}
void work()
{
	for(int i=1;i<=n;++i)
	{
		while(top&&a[steak[top]]<a[i])
		{
			c[steak[top-1]]+=c[steak[top]]+1;
			--top;
		}
		steak[++top]=i;
	}
	while(top)
	{
		c[steak[top-1]]+=c[steak[top]]+1;
		--top;
	}
	for(int i=1;i<=n;++i) ans+=c[i];
	printf("%I64d\n",ans);
}
int main()
{
	init();
	work();
	return 0;
}
