#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
int n,map[210][210],
vis[210],color[210],num[210][2],c,key[210],f[400][400],
pa[210],pb[210];
void init()
{
	int x,y,r;
	scanf("%d%d",&n,&r);
	memset(map,0,sizeof(map));
	memset(vis,false,sizeof(vis));
	memset(key,0,sizeof(key));
	memset(num,0,sizeof(num));
	memset(pa,0,sizeof(pa));
	memset(pb,0,sizeof(pb));
	memset(color,0,sizeof(color));
	c=0;
	for(int i=1;i<=r;++i)
	{
		scanf("%d%d",&x,&y);
		map[x][n+y]=map[n+y][x]=1;
	}
}
void dfs(int now, int p)
{
	vis[now]=true;
	color[now]=c;
	key[now]=p;
	int from=1,to=n;
	if(!p) from=n+1,to=n<<1;
	for(int i=from;i<=to;++i) if(!vis[i]&&map[now][i])
		dfs(i,1-p);
	++num[c][p];
}
void work()
{
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;++i)
		if(!vis[i])
		{
			++c;
			dfs(i,0);
		}
	for(int i=n+1;i<=n<<1;++i)
		if(!vis[i])
		{
			++c;
			dfs(i,1);
		}
	for(int i=1;i<=n;++i)
		for(int j=n+1;j<=n<<1;++j)
			if(color[i]==color[j]&&key[i]==key[j]&&map[i][j])
			{
				printf("0\n");
				return;
			}
	for(int i=1;i<=c;++i)
	{
		pa[i]=num[i][0];
		pb[i]=num[i][1];
	}
	f[0][0]=1;
	int ans=0;
	for(int i=1;i<=c;++i)
		for(int j=n>>1;j>=pa[i];--j)
			for(int k=n>>1;k>=pb[i];--k)
			{
				f[j][k]|=f[j-pa[i]][k-pb[i]];
				if(j==k&&f[j][k])
					ans=max(ans,j);
			}
	printf("%d\n",ans);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		init();
		work();
	}
	return 0;
}
