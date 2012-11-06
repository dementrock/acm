#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int g[13],f[13];
inline int min(int a, int b){return a>b?b:a;}
int main()
{
	g[1]=1;
	for(int i=2;i<=12;++i) g[i]=g[i-1]*2+1;
	f[1]=1;
	printf("1\n");
	for(int i=2;i<=12;++i)
	{
		f[i]=999999999;
		for(int j=1;j<i;++j)
			f[i]=min(f[i],2*f[j]+g[i-j]);
		printf("%d\n",f[i]);
	}
	return 0;
}
