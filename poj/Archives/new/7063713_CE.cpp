#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[2][60000],n,m,k,t,map1[160][20],map2[160][20],now;
void dfs(int x, int s1, int s2, int num)
{
	if(x>m+1) return;
	if(x==m+1){f[now&1][s1]>?=f[1-now&1][s2]+num;return;}
	if(!map1[now][x]) dfs(x+3,s1*27,s2*27+13,num+1);
	if(!map2[now][x]) dfs(x+2,s1*9,s2*9+8,num+1);
	dfs(x+1,s1*3,s2*3,num);
	dfs(x+1,s1*3+2,s2*3+1,num);
	dfs(x+1,s1*3+1,s2*3,num);
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int x,y;
		scanf("%d%d%d",&n,&m,&k);
		memset(map1,0,sizeof(map1));
		memset(map2,0,sizeof(map2));
		for(int i=1;i<=k;++i)
		{
			scanf("%d%d",&x,&y);
			for(int j=0;j<2;++j)
				for(int k=0;k<3;++k)
				{
					if(x+j<=n&&y-k>=1) map1[x+j][y-k]=1;
					if(x+k<=n&&y-j>=1) map2[x+k][y-j]=1;
				} 
		}
		for(int i=1;i<=n;++i) map2[2][i]=1;
		memset(f[1],0,sizeof(f[0]));
		for(now=2;now<=n;++now)
		{
			memset(f[now&1],0,sizeof(f[0]));
			dfs(1,0,0,0);
		}
		printf("%d\n",f[n&1][0]);
	}
	return 0;
}
