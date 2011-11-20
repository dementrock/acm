#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,f[101][3],edge[101][101],map[101][101],vis[101],oo=99999;
inline int min(int a, int b){return a>b?b:a;}
void dfs(int now)
{
	vis[now]=1;
	for(int i=1;i<=n;++i)
		if(!vis[i]&&map[now][i])
		{
			edge[now][++edge[now][0]]=i;
			dfs(i);
		}
}
void init()
{
	int x,y;
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		map[x][y]=map[y][x]=1;
	}
}
void dp(int x, int k)
{
	int sum=0;
	f[x][k]=oo;
	if(!edge[x][0])
	{
		if(k==1) f[x][k]=0;
		return;
	}
	for(int i=1;i<=edge[x][0];++i)
	{
		if(f[edge[x][i]][0]==-1) dp(edge[x][i],0);
		sum+=f[edge[x][i]][0];
	}
//	printf("%d %d %d\n",x,k,f[x][k]);
	if(k==0)
	{
		for(int i=1;i<=edge[x][0];++i)
			for(int j=1;j<=edge[x][0];++j) if(i!=j)
			{
				if(f[edge[x][i]][1]==-1) dp(edge[x][i],1);
				if(f[edge[x][i]][2]==-1) dp(edge[x][i],2);
				if(f[edge[x][j]][1]==-1) dp(edge[x][j],1);
				if(f[edge[x][j]][2]==-1) dp(edge[x][j],2);
				f[x][k]=min(f[x][k],
				sum-f[edge[x][i]][0]-f[edge[x][j]][0]+
				min(f[edge[x][i]][1],f[edge[x][i]][2])+
				min(f[edge[x][j]][1],f[edge[x][j]][2])+1);
			}
		for(int i=1;i<=edge[x][0];++i)
		{
			if(f[edge[x][i]][2]==-1) dp(edge[x][i],2);
			f[x][k]=min(f[x][k],sum-f[edge[x][i]][0]+f[edge[x][i]][2]+1);
		}
	}
	if(k==1)
	{
		f[x][k]=sum;
		return;
	}
	if(k==2)
	{
		for(int i=1;i<=edge[x][0];++i)
		{
			if(f[edge[x][i]][1]==-1) dp(edge[x][i],1);
			if(f[edge[x][i]][2]==-1) dp(edge[x][i],2);
			f[x][k]=min(f[x][k],sum-f[edge[x][i]][0]+f[edge[x][i]][1]);
			f[x][k]=min(f[x][k],sum-f[edge[x][i]][0]+f[edge[x][i]][2]);
		}
	}
//	printf("%d %d %d\n",x,k,f[x][k]);
}
void work()
{
	memset(f,0xff,sizeof(f));
	dfs(1);
	dp(1,0);
	if(f[1][0]<oo)
	printf("%d\n",f[1][0]);
	else printf("-1\n");
}
int main()
{
	init();
	work();
	return 0;
}
