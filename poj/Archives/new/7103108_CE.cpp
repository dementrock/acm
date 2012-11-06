#include<stdio.h>
int a[100001],stack[100001],f[100001],n,maxd,counter;
int init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
}
void work()
{
	stack[1]=f[1]=maxd=1;
	for(int i=2;i<=n;++i)
	{
		int l=1,r=maxd,m=0;
		while(l<=r)
		{
			m=l+r>>1;
			if(a[i]>a[stack[m]]) l=m+1;
			else r=m-1;
		}
		if(l>maxd) stack[++maxd]=i;
		if(a[i]<a[stack[l]]) stack[l]=i;
		f[i]=l;
	}
	printf("%d\n",maxd);
}
int main()
{
	init();
	work();
	return 0;
}
