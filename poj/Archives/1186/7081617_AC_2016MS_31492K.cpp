#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 4000037
int ans,n,m,p[10],k[10],item[200][10];
struct hashitem
{
	int s,n;
};
struct hash
{
	hashitem h[MAX];
	void add(int s)
	{
		int x=s>0?s:-s,i=x%MAX;
		while(h[i].s!=s&&h[i].n) i=(i+1)%MAX;
	//	printf("%d %d\n",s,i);
		h[i].s=s,++h[i].n;
	}
	void find(int s)
	{
		int x=s>0?s:-s,i=x%MAX;
		while(h[i].s!=s&&h[i].n) i=(i+1)%MAX;
		ans+=h[i].n;
	}
} h;
void dfs1(int deep, int now)
{
	if(deep==n/2+1)	h.add(now);
	else for(int i=1;i<=m;++i)
		dfs1(deep+1,now+item[i][deep]);
}
void dfs2(int deep, int now)
{
	if(deep==n+1) h.find(-now);
	else for(int i=1;i<=m;++i)
		dfs2(deep+1,now+item[i][deep]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%d",&k[i],&p[i]);
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)
		{
			item[i][j]=1;
			for(int k=1;k<=p[j];++k) item[i][j]*=i;
			item[i][j]*=k[j];
		}
	dfs1(1,0);
	dfs2(n/2+1,0);
	printf("%d\n",ans);
	return 0;
}
