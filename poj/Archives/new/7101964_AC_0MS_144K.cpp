#include<stdio.h>
#include<string.h>
int f[11][11],n,m;
void dp(int x, int y)
{
	f[x][y]=0;
	if(!x||y==1)
	{
		f[x][y]=1;
		return;
	}
	if(x-y>=0)
	{
		if(f[x-y][y]==-1) dp(x-y,y);
		f[x][y]+=f[x-y][y];
	}
	if(f[x][y-1]==-1) dp(x,y-1);
	f[x][y]+=f[x][y-1];
}
int main()
{
	int t;
	scanf("%d",&t);
	memset(f,0xff,sizeof(f));
	while(t--)
	{
		scanf("%d%d",&n,&m);
		if(f[n][m]==-1) dp(n,m);
		printf("%d\n",f[n][m]);
	}
	return 0;
}
