#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,a[101][101],f[101][101],ans;
inline int max(int a, int b){return a>b?a:b;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=i;++j) scanf("%d",&a[i][j]);
	for(int i=1;i<=n;++i)
	{
		f[i][1]=f[i-1][1]+a[i][1];
		for(int j=2;j<=i;++j)
		{
			f[i][j]=max(f[i-1][j],f[i-1][j-1]);
			f[i][j]+=a[i][j];
			ans=max(ans,f[i][j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
