#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[21][8193],m[21],n,s;
inline int max(int a, int b){return a>b?a:b;}
int dp(int now, int left)
{
	if(!left)
		return f[now][left]=1;
	else if(left==1)
		return f[now][left]=0;
	else
	{
		for(int i=max(0,left-m[now]);i<=left-1;++i)
		{
			if(f[now%n+1][i]==-1)
				f[now%n+1][i]=dp(now%n+1,i);
			if(!f[now%n+1][i]) return f[now][left]=1;
		}
	}
	return f[now][left]=0;
}
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		if(!n) break;
		scanf("%d",&s);
		memset(f,0xff,sizeof(f));
		memset(m,0,sizeof(m));
		n=n<<1;
		for(int i=1;i<=n;++i)
			scanf("%d",&m[i]);
		printf("%d\n",dp(1,s));
	}
	return 0;
}
