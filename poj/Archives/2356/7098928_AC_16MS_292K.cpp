#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 15001
int n,a[MAXN],s[MAXN],appear[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		s[i]=(s[i-1]+a[i])%n;
	}
	//if(n==1) printf("%d\n%d\n",1,a[1]);
	memset(appear,0xff,sizeof(appear));
	appear[0]=0;
	for(int i=1;i<=n;++i)
	{
		if(appear[s[i]]>=0)
		{
			printf("%d\n",i-appear[s[i]]);
			for(int j=appear[s[i]]+1;j<=i;++j)
				printf("%d\n",a[j]);
			break;
		}
		appear[s[i]]=i;
	}
	return 0;
}
