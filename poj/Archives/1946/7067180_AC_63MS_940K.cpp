#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[21][101][101],oo=99999999;
inline int min(int a, int b){return a>b?b:a;}
int n,e,d;
void dp(int i, int j, int k)
{
	f[i][j][k]=oo;
	if(j>k) return;
	if(i>1)
	{
		for(int x=0;x<=e;++x)
		{
			if(f[i-1][j][x]==-1) dp(i-1,j,x);
			f[i][j][k]=min(f[i][j][k],f[i-1][j][x]);
		}
	}
	int p=1;
	while(j-p>=0&&k-p*p>=0)
	{
		if(f[i][j-p][k-p*p]==-1) dp(i,j-p,k-p*p);
		f[i][j][k]=min(f[i][j][k],f[i][j-p][k-p*p]+1);
		++p;
	}
}
int main()
{
	int ans=oo;
	scanf("%d%d%d",&n,&e,&d);
	for(int i=1;i<=n;++i)
		for(int j=0;j<=d;++j)
			for(int k=0;k<=e;++k)
				f[i][j][k]=-1;
	for(int i=0;i<=e;++i) f[1][0][i]=0;
	for(int i=0;i<=e;++i)
	{
		if(f[n][d][i]==-1) dp(n,d,i);
		ans=min(ans,f[n][d][i]);
	}
	printf("%d\n",ans);
	return 0;
}
