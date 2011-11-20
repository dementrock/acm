#include<stdio.h>
int f[50][2],t,k;
int main()
{
	f[1][0]=f[1][1]=1;
	for(int i=2;i<=45;++i)
	{
		f[i][0]=f[i-1][0]+f[i-1][1];
		f[i][1]=f[i-1][0];
	}
	scanf("%d",&t);
	for(int i=1;i<=t;++i)
	{
		scanf("%d",&k);
		printf("Scenario #%d:\n%d\n\n",i,f[k][0]+f[k][1]);
	}
	return 0;
}
