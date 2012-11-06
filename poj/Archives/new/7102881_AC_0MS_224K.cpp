#include<stdio.h>
#include<string.h>
int n,v[101][101],f[101][101],oo,flag;
inline int max(int a, int b){return a<b?b:a;}
inline int min(int a, int b){return a>b?b:a;}
void init()
{
	int k,a,b;
	scanf("%d",&n);
	if(!n){flag=1;return;}
	memset(v,0x77,sizeof(v));
	memset(&oo,0x77,sizeof(oo));
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&k);
		for(int j=1;j<=k;++j)
		{
			scanf("%d%d",&a,&b);
			v[i][a]=b;
		}
	}
}
void work()
{
	int mint[101],mini=0,mintime=999999999;
	memcpy(f,v,sizeof(v));
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i) if(i!=k)
			for(int j=1;j<=n;++j) if(j!=k&&i!=j&&f[i][k]<oo&&f[k][j]<<oo)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	for(int i=1;i<=n;++i)
	{
		mint[i]=0;
		for(int j=1;j<=n;++j) if(j!=i)
			mint[i]=max(mint[i],f[i][j]);
		if(mint[i]<mintime)
		{
			mintime=mint[i];
			mini=i;
		}
	}
	if(!mini) printf("disjoint\n");
	else
	printf("%d %d\n",mini,mintime);
}
int main()
{
	while(1)
	{
		init();
		if(flag) break;
		work();
	}
	return 0;
}
