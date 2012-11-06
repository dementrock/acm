#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,k,t,T[101],P[101],S[101],f[101][30001],ans;
inline int max(int a, int b){return a>b?a:b;}
void dp(int x, int y)
{
	int tt=0;
	for(int i=1;i<=n;++i)
		if(T[i]==y&&S[i]==x)
			tt+=P[i];
	f[x][y]=0;
	if(y==0)
	{
		f[x][y]=tt;
		return;
	}
	if(x+1<=k)
	{
		if(f[x+1][y-1]==-1)dp(x+1,y-1);
		f[x][y]=max(f[x][y],f[x+1][y-1]);
	}
	if(x-1>=0)
	{
		if(f[x-1][y-1]==-1)dp(x-1,y-1);
		f[x][y]=max(f[x][y],f[x-1][y-1]);
	}
	if(f[x][y-1]==-1) dp(x,y-1);
	f[x][y]=max(f[x][y],f[x][y-1]);
	f[x][y]+=tt;
}
int main()
{
	scanf("%d%d%d",&n,&k,&t);
	memset(f,0xff,sizeof(f));
	for(int i=1;i<=n;++i) scanf("%d",&T[i]);
	for(int i=1;i<=n;++i) scanf("%d",&P[i]);
	for(int i=1;i<=n;++i) scanf("%d",&S[i]);
	for(int i=0;i<=k;++i)
	{
		if(f[i][t]==-1) dp(i,t);
		ans=max(f[i][t],ans);
	}
	printf("%d\n",ans);
	return 0;
}
