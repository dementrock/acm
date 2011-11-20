#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
int f[201][21][801],
	anslist[201],
	n,m,d[201],p[201],a[201],b[201],ans;
char choose[201][21][801];
inline int max(int a, int b){return a>b?a:b;}
void dp(int x, int y, int z)
{
	f[x][y][z]=-2;
	if(x<y) return;
	if(!y)
	{
		if(z==400)
			f[x][y][z]=0;
		return;
	}
	if(x==1)
	{
		if(z==400+a[x])
			f[x][y][z]=b[x];
		return;
	}
	if(f[x-1][y][z]==-1) dp(x-1,y,z);
	if(f[x-1][y][z]>f[x][y][z])
	{
		f[x][y][z]=f[x-1][y][z];
		choose[x][y][z]=0;	
	}
	if(z-a[x]>=0)
	{
		if(f[x-1][y-1][z-a[x]]==-1)
			dp(x-1,y-1,z-a[x]);
		if(f[x-1][y-1][z-a[x]]>=0)
			if(f[x-1][y-1][z-a[x]]+b[x]>f[x][y][z])
			{
				f[x][y][z]=f[x-1][y-1][z-a[x]]+b[x];
				choose[x][y][z]=1;
			}
	}
}
int main()
{
	int times=0;
	while(scanf("%d%d",&n,&m))
	{
		if(!n&&!m) break;
		++times;
		memset(f,0xff,sizeof(f));
		memset(choose,0,sizeof(choose));
		memset(anslist,0,sizeof(anslist));
		ans=99999;
		for(int i=1;i<=n;++i)
		{
			scanf("%d%d",&d[i],&p[i]);
			a[i]=d[i]-p[i],b[i]=d[i]+p[i];
		}
		for(int i=0;i<=400;++i)
		{
			if(f[n][m][400+i]==-1) dp(n,m,400+i);
			if(f[n][m][400-i]==-1) dp(n,m,400-i);
			
			if(f[n][m][400+i]>=0&&f[n][m][400-i]>=0)
			{
				if(f[n][m][400+i]>f[n][m][400-i])
					ans=i;
				else ans=-i;
				break;
			}
			if(f[n][m][400+i]>=0)
			{
				ans=i;
				break;
			}
			if(f[n][m][400-i]>=0)
			{
				ans=-i;
				break;
			}
		}
		int now=n,t=400+ans,mt=m;
		while(now!=1)
		{
			if(choose[now][mt][t])
			{
				anslist[++anslist[0]]=now;
				t-=a[now];
				--mt;
			}
			--now;	
		}
		if(mt==1) anslist[++anslist[0]]=1;	
	//	printf("%d %d\n",ans,f[n][m][400+ans]);
		int x1=0,x2=0;
		for(int i=1;i<=anslist[0];++i)
		{
			x1+=d[anslist[i]],x2+=p[anslist[i]];
		} 
		printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n",
		times,x1,x2);
		for(int i=anslist[0];i>=1;--i)
			printf(" %d",anslist[i]);
		printf("\n\n");
	}
	return 0;
}
