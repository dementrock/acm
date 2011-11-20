#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int a[20],deg[20],tdeg[20],map[20][20],vis[20],vis2[20],n,found=0,sum;
void swap(int &a, int &b){int x=a;a=b;b=x;}
void init()
{
	sum=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){ scanf("%d",&a[i]);sum+=a[i];}
	memcpy(deg,a,sizeof(a));
	memset(map,0,sizeof(map));
	memset(vis,0,sizeof(vis));
	found=0;
}
void work()
{
	while(1)
	{
		int maxdeg=0,maxi=0,maxj=0;
		for(int i=1;i<=n;++i) if(!vis[i])
			if(deg[i]>maxdeg)
			{
				maxdeg=deg[i];
				maxi=i;
			}
		if(maxdeg<=0)
		{
			if(maxdeg<0)
			{
				printf("NO\n");
				return;
			}
			for(int i=1;i<=n;++i)
			{
				int c=0;
				for(int j=1;j<=n;++j)
					c+=map[i][j];
				if(c!=a[i])
				{
					printf("NO\n");
					return;
				}
			}
			printf("YES\n");
			for(int i=1;i<=n;++i)
			{
				printf("%d",map[i][1]);
				for(int j=2;j<=n;++j)
					printf(" %d",map[i][j]);
				printf("\n");
			}
			return;
		}
		vis[maxi]=true;
		memset(vis2,0,sizeof(vis2));
		vis2[maxi]=true;
		for(int i=1;i<=deg[maxi];++i)
		{
			maxdeg=0;
			for(int j=1;j<=n;++j) if(!vis2[j])
				if(deg[j]>maxdeg)
				{
					maxdeg=deg[j];
					maxj=j;
				}
			vis2[maxj]=true;
			--deg[maxj];
			map[maxi][maxj]=map[maxj][maxi]=1;
		}
		deg[maxi]=0;
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		init();
		if(sum&1){printf("NO\n");if(t>=1) printf("\n");continue;}
		work();
		if(t>=1) printf("\n");
	}
	return 0;
}
