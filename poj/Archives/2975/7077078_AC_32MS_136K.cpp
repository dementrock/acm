#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int s[1001]={};
	while(1)
	{
		int n,ans=0,x=0;
		scanf("%d",&n);
		if(!n) break;
		for(int i=1;i<=n;++i)
		{
			scanf("%d",&s[i]);
			x^=s[i];
		}
		for(int i=1;i<=n;++i)
			if((x^s[i])<s[i])
				++ans;
		printf("%d\n",ans);
	}
	return 0;
}
