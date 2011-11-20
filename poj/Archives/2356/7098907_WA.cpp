#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 15001
int n,a[MAXN],f[MAXN],tf[MAXN],ans[MAXN],pre[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
	{
		f[a[i]%n]=1;
		pre[a[i]%n]=a[i]*10001;
	}
	for(int i=1;i<=n;++i)
	{
		memcpy(tf,f,sizeof(tf));
		for(int j=0;j<n;++j)
			if(f[j]&&!tf[(j+a[i])%n])
			{
				tf[(j+a[i])%n]=1;
				pre[(j+a[i])%n]=i;
		//		printf("%d %d %d\n",j,(j+a[i])%n,a[i]);
			}
		memcpy(f,tf,sizeof(tf));
	}
	if(!f[0])
		printf("0\n");
	else
	{
		int now=0;
		while(pre[now]<=10000)
		{
			ans[++ans[0]]=a[pre[now]];
			now=(now+n*n-a[pre[now]])%n;
		//	printf("%d\n",now);
		}
		ans[++ans[0]]=pre[now]/10001;
	}
	for(int i=0;i<=ans[0];++i)
		printf("%d\n",ans[i]);
	return 0;
}
