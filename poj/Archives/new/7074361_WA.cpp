#include<stdio.h>
#include<stdlib.h>
#define MAX 4000037
long long counter[MAX<<1],prodct[151][7],ans;
int k[151],p[151],n,m;
int hash(long long now)
{
	return now%MAX+MAX;
}
void dfs1(int deep, long long now)
{
	if(deep==(n>>1)+1)
		++counter[hash(now)];
	else
		for(int i=1;i<=m;++i)
			dfs1(deep+1,now+k[deep]*prodct[i][deep]%MAX);
}
void dfs2(int deep, long long now)
{
	if(deep==n+1)
		ans+=counter[hash(now)];
	else
		for(int i=1;i<=m;++i)
			dfs2(deep+1,now+k[deep]*prodct[i][deep]%MAX);
}
int main()
{
	scanf("%d",&n);
	scanf("%d",&m);
	if(n==1){ printf("1\n"); return 0;}
	for(int i=1;i<=n;++i)
		scanf("%d%d",&k[i],&p[i]);
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)
		{
			prodct[i][j]=1;
			for(int k=1;k<=p[j];++k)
				prodct[i][j]=prodct[i][j]*i%MAX;
		}
	dfs1(1,1);
	dfs2((n>>1)+1,1);
	printf("%I64d\n",ans);
	return 0;
}
