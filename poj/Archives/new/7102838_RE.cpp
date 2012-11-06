#include<stdio.h>
int a[500001],appear[1000001];
int main()
{
	a[0]=0;
	appear[0]=1;
	for(int i=1;i<=500000;++i)
	{
		if(a[i-1]-i>0&&!appear[a[i-1]-i])
			a[i]=a[i-1]-i;
		else a[i]=a[i-1]+i;
		appear[a[i]]=1;
	}
	while(1)
	{
		int t;
		scanf("%d",&t);
		if(t==-1) break;
		printf("%d\n",a[t]);
	}
	return 0;
}
