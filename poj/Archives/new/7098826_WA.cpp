#include<stdio.h>
#include<string.h>
#include<stdlib.h>
inline long long max(long long a, long long b){return a>b?a:b;}
inline long long min(long long a, long long b){return a<b?a:b;}
int main()
{
	while(1)
	{
		long long n,m;
		scanf("%I64d%I64d",&n,&m);
		if(!n&&!m) break;
		long long ans=1;
		for(long long i=n+m;i>max(n,m);--i)
			ans*=i;
		for(long long i=1;i<=min(n,m);++i)
			ans/=i;
		printf("%I64d\n",ans); 
	}
	return 0;
}
