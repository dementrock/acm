#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
int n,tmap[110][110],map[110][110],
vis[110],color[110],num[110][110],c,key[110],f[110][110],
pre[110][110],pos[110],neg[110];
void init()
{
	int x;
	
	freopen("1112.in","r",stdin);
	freopen("1112.out","w",stdout);
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
//	cout<<i<<"{"<<j<<endl;
	f[i][j]=0;
	int t=num[i][0]-num[i][1];
	if(i==1)
	{
		if(j==t||j==-t)
		{
			f[i][j]=1;
			pre[i][j]=(j==t?-1:1);
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
//	for(int i=1;i<=c;++i) cout<<num[i][0]<<" "<<num[i][1]<<endl;
	int now=-1,tmp;
	while(1)
	{
		++now;
		if(f[c][now]==-1) dp(c,now);
		if(f[c][now])
		{
	//		cout<<now<<endl;
			tmp=c;
			while(tmp)
			{
				if(pre[tmp][now]==1)
				{
					for(int i=1;i<=n;++i)
						if(color[i]==tmp&&!key[i])
							neg[++neg[0]]=i;
						else if(color[i]==tmp&&key[i])
							pos[++pos[0]]=i;
				}
				else
				{
					for(int i=1;i<=n;++i)
						if(color[i]==tmp&&key[i])
							neg[++neg[0]]=i;
						else if(color[i]==tmp&&!key[i])
							pos[++pos[0]]=i;
				}
				now+=pre[tmp][now]*(num[tmp][0]-num[tmp][1]);
				--tmp;
			}
			printf("%d",pos[0]);
			for(int i=1;i<=pos[0];++i) printf(" %d",pos[i]);
			printf("\n");
			printf("%d",neg[0]);
			for(int i=1;i<=neg[0];++i) printf(" %d",neg[i]);
			printf("\n");
			return;
		}
	}
}
int main()
{
	init();
	work();
	return 0;
}
