#include<stdio.h>
#include<stdlib.h>
struct feat
{
	int id,h;
} list[100001];
int n,k,ans,s[100001][31],a[100001][31];
inline int max(int a, int b)
{
	return a>b?a:b;
}
int hash(int s[])
{
	int res=0;
	for(int i=1;i<=k;++i)
		res=(res<<4)+s[i]*i*(s[i]+i);
	return res;
}
int cmp(const void *a, const void *b)
{
	feat *x=(feat*)a,*y=(feat*)b;
	if(x->h==y->h)
		return x->id-y->id;
	else
		return x->h-y->h;
}
int main()
{
	int x;
	scanf("%d%d",&n,&k);
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
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=k;++j)
			s[i][j]-=s[i][k];
		list[i].h=hash(s[i]);
		list[i].id=i;
	}
	list[0].h=0;
	list[0].id=0;
	qsort(list,n,sizeof(list[0]),cmp);
	int i=0;
	while(i<=n)
	{
		int j=i;
		while(list[j].h==list[i].h) ++j;
		ans=max(ans,list[j-1].id-list[i].id);
		i=j;
	}
	printf("%d\n",ans);
	return 0;
}
