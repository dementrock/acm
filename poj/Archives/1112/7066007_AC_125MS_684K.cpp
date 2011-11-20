#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
int n,tmap[110][110],map[110][110],
vis[110],color[110],num[110][110],c,key[110],f[110][500],
pre[110][500],now,ans[2][110];
void init()
{
	int x;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		while(1)
		{
			scanf("%d",&x);
			if(!x) break;
			tmap[i][x]=1;
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j&&!(tmap[i][j]&&tmap[j][i]))
				map[i][j]=1;
}
void dfs(int now, int p)
{
	vis[now]=true;
	color[now]=c;
	key[now]=p;
	for(int i=1;i<=n;++i) if(!vis[i]&&map[now][i])
		dfs(i,1-p);
	++num[c][p];
}
void dp(int i, int j)
{
	f[i][j]=0;
	int t=num[i][0]-num[i][1];
	if(i==1)
	{
		if(j==200+t||j==200-t)
		{
			f[i][j]=1;
			pre[i][j]=(j==200+t?-1:1);
		}
		return;
	}
	if(j-t>=0)
	{
		if(f[i-1][j-t]==-1) dp(i-1,j-t);
		if(f[i-1][j-t])
		{
			f[i][j]=1;
			pre[i][j]=-1;
		}
	}
	if(j+t>=0)
	{
		if(f[i-1][j+t]==-1) dp(i-1,j+t);
		if(f[i-1][j+t])
		{
			f[i][j]=1;
			pre[i][j]=1;
		}
	}
}
void work()
{
	memset(f,0xff,sizeof(f));
	for(int i=1;i<=n;++i)
		if(!vis[i])
		{
			++c;
			dfs(i,0);
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(color[i]==color[j]&&key[i]==key[j]&&map[i][j])
			{
				printf("No solution\n");
				return;
			}
	now=-1;
	int tnow=999999;
	int tmp;
	for(now=0;now<=400;++now)
	{
		if(f[c][now]==-1) dp(c,now);
		if(f[c][now]==1&&abs(now-200)<abs(tnow-200))
			tnow=now;
	}
	now=tnow;
	tmp=c;
	while(tmp)
	{
		int t=pre[tmp][now]==1?1:0;
		for(int i=1;i<=n;++i)
			if(color[i]==tmp&&!key[i])
				ans[t][++ans[t][0]]=i;
			else if(color[i]==tmp&&key[i])
				ans[1-t][++ans[1-t][0]]=i;
		now+=pre[tmp][now]*(num[tmp][0]-num[tmp][1]);
		--tmp;
	}
	for(int i=0;i<=1;++i)
	{
		printf("%d",ans[i][0]);
		for(int j=1;j<=ans[i][0];++j) printf(" %d",ans[i][j]);
		printf("\n");
	}
}
int main()
{
	init();
	work();
	return 0;
}
