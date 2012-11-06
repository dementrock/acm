#include<stdio.h>
#include<string.h>
#define MAXN 50001
int father[MAXN],vis[MAXN],ans;
int getfather(int x)
{
	if(father[x]==x) return x;
	return father[x]=getfather(father[x]);
}
void together(int a, int b)
{
	int x=getfather(a),y=getfather(b);
	father[x]=y;
}
int main()
{
	int t=0,n,m,x,y;
	while(scanf("%d%d",&n,&m))
	{
		if(!n&&!m) break;
		++t;
		ans=0;
		for(int i=1;i<=n;++i)
			father[i]=i;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=m;++i)
		{
			scanf("%d%d",&x,&y);
			together(x,y);
		}
		for(int i=1;i<=n;++i)
			vis[getfather(i)]=1;
		for(int i=1;i<=n;++i)
			ans+=vis[i];
		printf("Case %d: %d\n",t,ans);
	}
	return 0;
}
