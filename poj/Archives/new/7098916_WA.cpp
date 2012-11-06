#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 15001
int n,a[MAXN],s[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		s[i]=(s[i-1]+a[i])%n;
	}
	if(n==1) printf("%d\n%d\n",1,a[1]);
	for(int i=2;i<=n;++i)
		if(s[i]==s[1])
		{
			printf("%d\n",i-1);
			for(int j=2;j<=i;++j)
				printf("%d\n",a[j]);
			break;
		}
	return 0;
}
