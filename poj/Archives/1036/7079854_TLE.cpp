#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,k,t,T[101],P[101],S[101],*f[30001],ans;
inline int max(int a, int b){return a>b?a:b;}
void dp(int x, int y)
{
	f[y][x]=0;
	if(y==0&&x!=0||x>y) return;
	int tt=0;
	for(int i=1;i<=n;++i)
		if(T[i]==y&&S[i]==x)
			tt+=P[i];
	if(y==0)
	{
		f[y][x]=tt;
		return;
	}
	if(x+1<=k)
		f[y][x]=max(f[y][x],f[y-1][x+1]);
	if(x-1>=0)
		f[y][x]=max(f[y][x],f[y-1][x-1]);
	f[y][x]=max(f[y][x],f[y-1][x]);
	f[y][x]+=tt;
}
int main()
{
	scanf("%d%d%d",&n,&k,&t);
	for(int i=1;i<=n;++i) scanf("%d",&T[i]);
	for(int i=1;i<=n;++i) scanf("%d",&P[i]);
	for(int i=1;i<=n;++i) scanf("%d",&S[i]);
	for(int i=0;i<=t;++i)
	{
		f[i]=new int[k+1];
		for(int j=0;j<=k;++j)
		{
			dp(j,i);
			if(i==t) ans=max(f[i][j],ans);
		}
		if(i) delete [] f[i-1];
	}
	printf("%d\n",ans);
	return 0;
}
