#include<stdio.h>
#include<stdlib.h>
#include<string.h>
long long f[14][14][9000],num[14][14][9000],ans,ansnum;
int v[14],map[14][14],n,m;
void dp(int deep, int i, int j, int S)
{
	if(deep==2)
	{
		f[i][j][S]=v[i]+v[j]+v[i]*v[j];
		num[i][j][S]=1;
		return;
	}
	f[i][j][S]=0;
	num[i][j][S]=1;
	int ts=S;
	for(int k=1;k<=n;++k) 
	{
		int now=ts&1;
		ts>>=1;
		if(map[j][k]&&now&&k!=i&&k!=j)
		{
			if(f[j][k][S-(1<<(i-1))]==-1)
				dp(deep-1,j,k,S-(1<<(i-1)));
			if(!f[j][k][S-(1<<(i-1))]) continue;
			long long fnow=f[j][k][S-(1<<(i-1))]+v[i]+v[i]*v[j];
			if(map[k][i]) fnow+=v[k]*v[j]*v[i];
			if(fnow>f[i][j][S])
			{
				f[i][j][S]=fnow;
				num[i][j][S]=num[j][k][S-(1<<(i-1))];
			}
			else if(fnow==f[i][j][S])
				num[i][j][S]+=num[j][k][S-(1<<(i-1))];
		}
	}
}
int main()
{
	int qqq,x,y;
	scanf("%d",&qqq);
	while(qqq--)
	{
		memset(v,0,sizeof(v));
		memset(map,0,sizeof(map));
		memset(f,0xff,sizeof(f));
		memset(num,0,sizeof(num));
		ans=ansnum=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i) scanf("%d",&v[i]);
		for(int i=1;i<=m;++i)
		{
			scanf("%d%d",&x,&y);
			if(x!=y)
				map[x][y]=map[y][x]=1;
		}
		if(n==1)
		{
			printf("%d %d\n",v[1],1);
			continue;
		}
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j) if(map[i][j])
			{
				if(f[i][j][(1<<n)-1]==-1)
				{
					dp(n,i,j,(1<<n)-1);
					if(f[i][j][(1<<n)-1]>ans)
					{
						ans=f[i][j][(1<<n)-1];
						ansnum=num[i][j][(1<<n)-1];
					}
					else if(f[i][j][(1<<n)-1]==ans)
						ansnum+=num[i][j][(1<<n)-1];
				}
			}
		if(!ans)
			printf("0 0\n");
		else printf("%I64d %I64d\n",ans,ansnum>>1);
	}
}
