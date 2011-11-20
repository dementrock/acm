#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 101
int T[MAXN][MAXN],V[MAXN][MAXN],P[MAXN],L[MAXN],
X[MAXN],que[MAXN],v[MAXN][MAXN],canuse[MAXN],m,n,
dis[MAXN],vis[MAXN],Closed,Open,oo=999999999,ans=oo;
inline int min(int a, int b){return a>b?b:a;}
void init()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d%d",&P[i],&L[i],&X[i]);
		for(int j=1;j<=X[i];++j)
			scanf("%d%d",&T[i][j],&V[i][j]);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=X[i];++j)
			v[T[i][j]][i]=V[i][j];
	for(int i=1;i<=n;++i) v[0][i]=P[i];
}
int spfa(int s)
{
	int mindis;
	memset(&mindis,0x77,sizeof(mindis));
	memset(dis,0x77,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(que,0,sizeof(que));
	if(!canuse[1]) return mindis;
	dis[s]=0;
	vis[s]=true;
	que[0]=s;
	Closed=-1;
	Open=0;
	while(Closed!=Open)
	{
		Closed=(Closed+1)%(n+1);
		int now=que[Closed];
		for(int i=0;i<=n;++i) if(canuse[i]) if(v[now][i])
			if(dis[now]+v[now][i]<dis[i])
			{
				dis[i]=dis[now]+v[now][i];
				
		//		printf("%d %d %d\n",now,i,dis[i]);
				if(!vis[i])
				{
					vis[i]=true;
					Open=(Open+1)%(n+1);
					que[Open]=i;
				}
			}
		vis[now]=false;
	}
//	for(int i=1;i<=n;++i) printf("%d ",dis[i]);
//	printf("\n");
	return dis[1];
}
void work()
{
	for(int i=1;i<=n;++i)
	{
		memset(canuse,true,sizeof(canuse));
		for(int j=1;j<=n;++j) if(L[j]<L[i]-m) canuse[j]=false;
		ans=min(ans,spfa(0));
	}
	printf("%d\n",ans);
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	init();
	work();
	return 0;
}
