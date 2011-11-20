#include<stdio.h>
#include<stdlib.h>
int f[13][5000],state[13],line[13][5000],a[13][13],m,n,ans;
void dfs(int row, int now, int s)
{
	if(now>n+1) return;
	if(now==n+1)
	{
		line[row][++state[row]]=s;
		return;
	}
	if(a[row][now])
	{
		if(now+2<=n+1)
			dfs(row,now+2,((s<<1)+1)<<1);
		else dfs(row,now+1,(s<<1)+1);
	}
	dfs(row,now+1,s<<1);
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&a[i][j]);
	state[0]=1;
	line[0][1]=0;
	f[0][1]=1;
	for(int i=1;i<=m;++i)
	{
		dfs(i,1,0);
		for(int j=1;j<=state[i];++j)
			for(int k=1;k<=state[i-1];++k)
			{
				if(line[i][j]&line[i-1][k]) continue;
				f[i][j]+=f[i-1][k];
			}
	}
	for(int i=1;i<=state[m];++i) ans+=f[m][i];
	printf("%d\n",ans);
	return 0;
}
