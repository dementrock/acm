#include<stdio.h>
int a[1501]={};
int main()
{
	int p[6]={},plist[]={2,3,5};
	p[2]=1,p[3]=1,p[5]=1;
	a[1]=1;
	for(int i=2;i<=1501;++i)
	{
		int minv=0x77777777,mint=0;
		for(int j=0;j<3;++j)
		{
			int t=a[p[plist[j]]]*plist[j];
			while(t<=a[i-1]){ ++p[plist[j]];t=a[p[plist[j]]]*plist[j];}
			if(t<minv)
			{
				minv=t;
				mint=plist[j];
			}
		}
		a[i]=minv;
		++p[mint];
	}
	while(1)
	{
		int n;
		scanf("%d",&n);
		if(!n) break;
		printf("%d\n",a[n]);
	}
	return 0;
}
