#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int MAXV=100000;
long long ans=0;
int v,e,degree[MAXV+1],que[MAXV+1],*map[MAXV+1],*edge[MAXV+1],dis[MAXV+1],vis[MAXV+1],x[MAXV+1],y[MAXV+1],z[MAXV+1],w[MAXV+1];
void spfa(int s)
{
	memset(dis,0x77,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(que,0,sizeof(que));
	int closed=0,open=1;
	que[1]=s;
	dis[s]=0;
	vis[s]=true;
	while(closed!=open)
	{
		closed=closed%v+1;
		int now=que[closed];
		for(int i=1;i<=map[now][0];++i)
		{
			int to=map[now][i];
			if(dis[now]+edge[now][i]<dis[to])
			{
				dis[to]=dis[now]+edge[now][i];
				if(!vis[to])
				{
					vis[to]=true;
					open=open%v+1;
					que[open]=to;
				}
			}
		}
		vis[now]=false;
	}
}
void work()
{
	for(int i=1;i<=v;++i)
	{	
		if(!degree[i])
		{
			printf("No Answer\n");
			return;
		}
		map[i]=new int [degree[i]+1];
		memset(map[i],0,sizeof(map[i]));
		edge[i]=new int [degree[i]+1];
		memset(edge[i],0,sizeof(edge[i]));
	}
	for(int i=1;i<=e;++i)
	{
		map[x[i]][++map[x[i]][0]]=y[i];
		edge[x[i]][++edge[x[i]][0]]=z[i];
		map[y[i]][++map[y[i]][0]]=x[i];
		edge[y[i]][++edge[y[i]][0]]=z[i];
	}
	spfa(1);
	for(int i=1;i<=v;++i)
	{
		delete [] map[i];
		delete [] edge[i];
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		memset(degree,0,sizeof(degree));
		memset(w,0,sizeof(w));
		memset(x,0,sizeof(x));
		memset(y,0,sizeof(y));
		memset(z,0,sizeof(z));
		scanf("%d%d",&v,&e);
		for(int i=1;i<=v;++i) scanf("%d",&w[i]);
		for(int i=1;i<=e;++i)
		{
			scanf("%d%d%d",&x[i],&y[i],&z[i]);
			++degree[x[i]];++degree[y[i]];
		}
		if(!v||v==1)
		{
			printf("0\n");
			continue;
		}
		work();
		for(int i=1;i<=v;++i) ans+=dis[i]*w[i];
		printf("%I64d\n",ans);
	}
	return 0;
}
