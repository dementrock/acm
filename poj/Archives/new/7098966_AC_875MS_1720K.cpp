#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 200001
int n,m,a[MAXN],s[MAXN],appear[MAXN];
int main()
{
	while(1)
	{
		scanf("%d%d",&n,&m);
		if(!n&&!m) break;
		for(int i=1;i<=m;++i)
		{
			scanf("%d",&a[i]);
			s[i]=(s[i-1]+a[i])%n;
		}
		memset(appear,0xff,sizeof(appear));
		appear[0]=0;
		for(int i=1;i<=n;++i)
		{
			if(appear[s[i]]>=0)
			{
				for(int j=appear[s[i]]+1;j<=i;++j)
				{
					printf("%d",j);
					if(j<i) printf(" ");
					else printf("\n");
				}
				break;
			}
			appear[s[i]]=i;
		}
	}
	return 0;
}
