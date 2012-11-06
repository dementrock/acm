#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 201
int T[MAXN][MAXN],V[MAXN][MAXN],P[MAXN],L[MAXN],
X[MAXN],que[MAXN],v[MAXN][MAXN],m,n,
dis[MAXN],minl[MAXN],maxl[MAXN],
vis[MAXN],Closed,Open,
oo=999999999,ans=oo;
bool canuse[MAXN];
inline int min(int a, int b){return a>b?b:a;}
inline int max(int a, int b){return a<b?b:a;}
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
int spfa(int s, int nows)
{
	int mindis;
	memset(&mindis,0x77,sizeof(mindis));
	memset(dis,0x77,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(que,0,sizeof(que));
	for(int i=1;i<=n;++i) minl[i]=L[i]-m,maxl[i]=L[i]+m;
	minl[0]=-oo,maxl[0]=oo;
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
		for(int i=0;i<=n;++i) if(now==0&&i==nows||now&&canuse[i]) if(v[now][i])
			if(minl[now]<=L[i]&&L[i]<=maxl[now])
			if(dis[now]+v[now][i]<dis[i])
			{
				dis[i]=dis[now]+v[now][i];
			//	printf("%d %d %d\n",now,i,dis[i]);
				minl[i]=max(minl[i],minl[now]);
				maxl[i]=min(maxl[i],maxl[now]);
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
//		printf("%d\n",i);
		memset(canuse,true,sizeof(canuse));
		for(int j=1;j<=n;++j) if(L[j]>L[i]+m||L[j]<L[i]-m) canuse[j]=false;
//		for(int j=1;j<=n;++j) printf("%d ",canuse[j]);
//		printf("\n");
		ans=min(ans,spfa(0,i));
	}
	printf("%d\n",ans);
}
int main()
{
	init();
	work();
	return 0;
}
