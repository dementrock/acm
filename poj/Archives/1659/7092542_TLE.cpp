#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int a[20],deg[20],map[20][20],n,found=0;
void swap(int &a, int &b){int x=a;a=b;b=x;}
void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<n;++j) 
			if(a[j]>a[j+1]) swap(a[j],a[j+1]);
	memcpy(deg,a,sizeof(a));
	memset(map,0,sizeof(map));
	found=0;
}
void dfs(int deep1, int deep2, int last, int maxd2) //deep1:搜索到的节点编号 deep2:对该节点度数进行搜索
{													//last  对该节点度数进行搜索的上一个节点 maxd2 deep2最大深度 
	if(found) return;
	if(deep1==n+1)
	{
		int tdeg[20]={};
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(map[i][j])
					++tdeg[i],++tdeg[j];
		for(int i=1;i<=n;++i)
			for(int j=1;j<n;++j)
				if(tdeg[j]>tdeg[j+1])
					swap(tdeg[j],tdeg[j+1]);
		for(int i=1;i<=n;++i)
			if(tdeg[i]!=a[i]*2)
				return;
		printf("YES\n");
		for(int i=1;i<=n;++i)
		{
			printf("%d",map[i][1]);
			for(int j=2;j<=n;++j)
				printf(" %d",map[i][j]);
			printf("\n");
		}
		found=1;
		return;
	}
	if(deep2==maxd2+1)
	{
		dfs(deep1+1,1,0,a[deep1+1]);
		return;
	}
	for(int i=last+1;i<=n;++i)
		if(deg[i]&&deep1!=i)
		{
			--deg[i];
			map[deep1][i]=1;
			dfs(deep1,deep2+1,i,maxd2);
			if(found) return;
			map[deep1][i]=0;
			++deg[i];
		}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		init();
		dfs(1,1,0,a[1]);
		if(!found) printf("NO\n");
		if(t>=1) printf("\n");
	}
	return 0;
}
