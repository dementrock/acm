#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct feat
{
	int id;
	int s[31];
} list[100001];
int n,k,ans,s[100001][31],a[100001][31];
inline int max(int a, int b)
{
	return a>b?a:b;
}
int cmp(const void *a, const void *b)
{
	feat *x=(feat*)a,*y=(feat*)b;
	for(int i=1;i<=k;++i)
		if(x->s[i]!=y->s[i])
			return x->s[i]-y->s[i];
	return x->id-y->id;
}
int equal(feat a, feat b)
{
	for(int i=1;i<=k;++i)
		if(a.s[i]!=b.s[i])
			return 0;
	return 1;
}
int main()
{
	int x;
	scanf("%d%d",&n,&k);
//	printf("%d %d\n",n,k);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&x);
		for(int j=1;j<=k;++j)
		{
			int t=x&1;
			a[i][j]=t;
			s[i][j]=s[i-1][j]+t;
			x=x>>1;
		}
	//	for(int j=1;j<=k;++j) s[i][j]-=s[i][k];
	}
	for(int i=0;i<=n;++i)
	{
		for(int j=1;j<=k;++j)
			s[i][j]-=s[i][k];
		list[i].id=i;
		memcpy(list[i].s,s[i],sizeof(s[i]));
	}
	qsort(list,n+1,sizeof(list[0]),cmp);
	int i=0;
	while(i<=n)
	{
		int j=i;
		while(equal(list[j],list[i])&&j<=n) ++j;
		ans=max(ans,list[j-1].id-list[i].id);
		i=j;
	}
	printf("%d\n",ans);
	return 0;
}
