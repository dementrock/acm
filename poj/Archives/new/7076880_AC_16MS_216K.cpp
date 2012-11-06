#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int r,c,f[101][101],snow[101][101];
int move[4][2]={{-1,0},{1,0},{0,1},{0,-1}},ans;
inline int max(int a, int b){return a>b?a:b;}
void dp(int x, int y)
{
	f[x][y]=1;
	for(int i=0;i<4;++i)
	{
		int tx=x+move[i][0],ty=y+move[i][1];
		if(1<=tx&&tx<=r&&1<=ty&&ty<=c)
			if(snow[x][y]>snow[tx][ty])
			{
				if(f[tx][ty]==-1) dp(tx,ty);
				f[x][y]=max(f[x][y],f[tx][ty]+1);
			}
	}
}
int main()
{
	scanf("%d%d",&r,&c);
	memset(f,0xff,sizeof(f));
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j)
			scanf("%d",&snow[i][j]);
	for(int i=1;i<=r;++i)
		for(int j=1;j<=c;++j)
		{
			if(f[i][j]==-1)
				dp(i,j);
			ans=max(ans,f[i][j]);
		}
	printf("%d\n",ans);
	return 0;
}
