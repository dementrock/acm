#include<stdio.h>
int now,appear[1000000],n;
int get(int now)
{
	now=(now/10)%10000;
	now*=now;
	now%=1000000;
	return now;
}
int main()
{
	scanf("%d",&now);
	appear[now]=1;
	int n=1;
	while(1)
	{
		++n;
		now=get(now);
		if(appear[now])
		{
			printf("%d %d %d\n",now,n-appear[now],n-1);
			break;
		}
		appear[now]=n;
	}
	return 0;
}
