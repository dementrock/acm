#include<stdio.h>
#include<string.h>
int a[40001],f[40001],stack[40001],maxd,n;
void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
}
void work()
{
	memset(stack,0,sizeof(stack));
	stack[1]=maxd=f[1]=1;
	for(int i=2;i<=n;++i)
	{
		int l=1,r=maxd,m;
		while(l<=r)
		{
			m=l+r>>1;
			if(a[i]>a[stack[m]]) l=m+1;
			else r=m-1;
		}
		if(l>maxd)
			stack[++maxd]=i;
		if(a[i]<a[stack[l]]) stack[l]=i;
		f[i]=l;
	}
	printf("%d\n",maxd);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		init();
		work();
	}
	return 0;
}
