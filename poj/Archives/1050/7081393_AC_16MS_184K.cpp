#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int ans,f[101],b[101],a[101][101],n;
inline int max(int a, int b){return a>b?a:b;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;++i)
	{
		memset(b,0,sizeof(b));
		for(int j=i;j<=n;++j)
		{
			memset(f,0,sizeof(f));
			for(int k=1;k<=n;++k) b[k]+=a[j][k];
			for(int k=1;k<=n;++k)
			{
				f[k]=max(b[k],b[k]+f[k-1]);
				ans=max(ans,f[k]);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
