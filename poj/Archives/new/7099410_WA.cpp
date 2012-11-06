#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[101][101],c[101],a[101],n,m;
void dp(int n, int k)
{
	if(n==0)
	{
		if(k!=0) f[n][k]=0;
		else f[n][k]=1;
		return;
	}
	if(k==0)
	{
		f[n][k]=1;
		return;
	}
	if(f[n-1][k]<0) dp(n-1,k);
	f[n][k]=f[n-1][k];
	if(!c[n]) return;
	for(int i=1;i<=c[n]&&k-i>=0;++i)
	{
		if(f[n-1][k-i]<0)
			dp(n-1,k-i);
		f[n][k]+=f[n-1][k-i];
	}
}
int main()
{
	int num=0,r;
	while(1)
	{
		++num;
		memset(f,0xff,sizeof(f));
		memset(c,0,sizeof(c));
		scanf("%d",&n);
		if(!n) break;
		printf("Case %d:\n",num);
		scanf("%d",&m);
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&a[i]);
			++c[a[i]];
		}
		for(int i=1;i<=m;++i)
		{
			scanf("%d",&r);
			if(f[n][r]<0) dp(n,r);
			printf("%d\n",f[n][r]);
		}
	}
	return 0;
}
