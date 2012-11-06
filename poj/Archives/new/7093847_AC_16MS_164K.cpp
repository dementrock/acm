#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 1001
int a[MAXN],b[MAXN],appear[MAXN],f[MAXN],s[MAXN],n,ans;
void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;++i) appear[b[i]]=i;
	for(int i=1;i<=n;++i) f[i]=appear[a[i]];
}
inline int lowbit(int x){return x&(-x);}
int getsum(int now)
{
	int t=0;
	for(int i=now;i>=1;i-=lowbit(i))
		t+=s[i];
	return t;
}
void add(int now, int d)
{
	for(int i=now;i<=n;i+=lowbit(i))
		s[i]+=d;
}
void work()
{
	for(int i=1;i<=n;++i)
	{
		ans+=i-getsum(f[i])-1;
		add(f[i],1);
	}
	printf("%d\n",ans);
}
int main()
{
	init();
	work();
	return 0;
}
