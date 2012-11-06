#include<stdio.h>
int a[100001],stack[100001],f[100001],n,maxd,counter;
int init()
{
	n=1;
	scanf("%d",&a[1]);
	if(a[1]==-1) return 0;
	while(scanf("%d",&a[++n]))
		if(a[n]==-1) break;
	--n;
	return 1;
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
			if(a[i]<a[stack[m]]) l=m+1;
			else r=m-1;
		}
		if(l>maxd) stack[++maxd]=i;
		if(a[i]>a[stack[l]]) stack[l]=i;
		f[i]=l;
	}
	printf("Test #%d:\n  maximum possible interceptions: %d\n\n",counter,maxd);
}
int main()
{
	while(1)
	{
		++counter;
		if(!init()) break;
		work();
	}
	return 0;
}
