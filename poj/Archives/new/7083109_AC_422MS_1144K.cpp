#include<stdio.h>
#include<stdlib.h>
int n,a[100002],f1[100002],f2[100002],max1[100002],max2[100002],oo=999999999,ans=-oo,t;
inline int max(int a, int b){return a>b?a:b;}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		if(!n) break;
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		for(int i=0;i<=n+1;++i) f1[i]=f2[i]=max1[i]=max2[i]=ans=-oo;
		for(int i=1;i<=n;++i){ f1[i]=max(a[i],a[i]+f1[i-1]);max1[i]=max(max1[i-1],f1[i]);}
		for(int i=n;i>=1;--i){ f2[i]=max(a[i],a[i]+f2[i+1]);max2[i]=max(max2[i+1],f2[i]);}
		for(int i=1;i<=n;++i) ans=max(ans,max1[i-1]+max2[i]);
		printf("%d\n",ans);
	}
	return 0;
} 
