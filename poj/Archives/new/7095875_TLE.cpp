#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct news
{
	int t,c;
} bus[60];
struct Route
{
	int c,t[60];
} route[60][60];
int n,num[60],routenum[60],ans=99999999,tans;
inline int min(int a, int b){return a>b?b:a;}
void swap(Route &a, Route &b){Route x=a;a=b;b=x;}
void init()
{
	int tn,t,tc[301]={};
	scanf("%d",&tn);
	for(int i=1;i<=tn;++i)
	{
		scanf("%d",&t);
		++tc[t];
	}
	for(int i=0;i<=59;++i)
		if(tc[i])
		{
			bus[++n].t=i;
			bus[n].c=tc[i];
			num[n]=tc[i];
		}
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
		{
			route[i][++routenum[i]].t[++route[i][routenum[i]].c]=i;
			route[i][routenum[i]].t[++route[i][routenum[i]].c]=j;
			int t=j;
			while(1)
			{
				bool flag=false;
				for(int k=j+1;k<=n;++k) if(bus[k].t-bus[t].t==bus[j].t-bus[i].t)
				{
					flag=true;
					t=k;
					break;
				}
				if(!flag) break;
				route[i][routenum[i]].t[++route[i][routenum[i]].c]=t;
			}
		}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=routenum[i];++j)
			for(int k=1;k<routenum[i];++k)
				if(route[i][k].c<route[i][k+1].c)
					swap(route[i][k],route[i][k+1]);
	/*for(int i=1;i<=n;++i)
	{
		printf("Route<%d>\n",i);
		for(int j=1;j<=routenum[i];++j)
		{
			for(int k=1;k<=route[i][j].c;++k)
				printf("%d ",bus[route[i][j].t[k]].t);
			printf("\n");
		}
	}*/
}
void dfs(int now)
{
	if(tans>17) return;
	if(tans+1>ans) return;
	if(now==n+1)
	{
		ans=min(ans,tans);
		return;
	}
	if(!num[now])
	{
		dfs(now+1);
		return;
	}
	for(int i=1;i<=routenum[now];++i)
	{
		bool flag=true;
		for(int j=1;j<=route[now][i].c;++j)
			if(!num[route[now][i].t[j]])
			{
				flag=false;
				break;
			}
		if(!flag) continue;
		for(int j=1;j<=route[now][i].c;++j)
			--num[route[now][i].t[j]];
		++tans;
		dfs(now+1);
		--tans;
		for(int j=1;j<=route[now][i].c;++j)
			++num[route[now][i].t[j]];
	}
}
void work()
{
	dfs(1);
	printf("%d\n",ans);
}
int main()
{
	init();
	work();
	return 0;
}
