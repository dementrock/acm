#include<stdio.h>
int f[10001]={};
inline int min(int a, int b){return a>b?b:a;}
inline int max(int a, int b){return a<b?b:a;}
void get(int x)
{
	int t=x;
	++f[x];
	while(t!=1)
	{
		++f[x];
		if(t&1) t=3*t+1;
		else t=t>>1;
	}
}
int main()
{
	int n,m;
	for(int i=1;i<=10000;++i) get(i);
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		int ans=0;
		printf("%d %d ",n,m);
		for(int i=min(n,m);i<=max(n,m);++i)
			if(f[i]>ans) ans=f[i];
		printf("%d\n",ans);
	}
	return 0;
}
