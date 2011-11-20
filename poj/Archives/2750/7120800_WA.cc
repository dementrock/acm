#include<stdio.h>
#define MAXN 100001
int sum[8*MAXN],lmaxsum[8*MAXN],rmaxsum[8*MAXN],lminsum[8*MAXN],rminsum[8*MAXN],maxsum[8*MAXN],minsum[8*MAXN],a[MAXN];
inline int max(int a, int b)
{
	return a>b?a:b; 
}
inline int min(int a, int b)
{
	return a<b?a:b;
}
void insert(int p, int left, int right, int x, int key)
{
	if(left==right)
	{
		sum[p]=key;
		maxsum[p]=max(0,key);
		minsum[p]=min(0,key);
		return;
	}
	int mid=left+right>>1;
	if(x<=mid)
		insert(p*2,left,mid,x,key);
	else
		insert(p*2+1,mid+1,right,x,key);
	sum[p]=sum[p]-a[x]+key;
//	printf("%d %d add: %d\n",left,right,sum[p]);
	lmaxsum[p]=lmaxsum[p*2];
	lmaxsum[p]=max(lmaxsum[p],sum[p]-sum[p*2+1]);
	lmaxsum[p]=max(lmaxsum[p],sum[p]-sum[p*2+1]+lmaxsum[p*2+1]);
	rmaxsum[p]=rmaxsum[p*2+1];
	rmaxsum[p]=max(rmaxsum[p],sum[p]-sum[p*2]);
	rmaxsum[p]=max(rmaxsum[p],sum[p]-sum[p*2]+rmaxsum[p*2]);
	lminsum[p]=lminsum[p*2];
	lminsum[p]=min(lminsum[p],sum[p]-sum[p*2+1]);
	lminsum[p]=min(lminsum[p],sum[p]-sum[p*2+1]+lminsum[p*2+1]);
	rminsum[p]=rminsum[p*2+1];
	rminsum[p]=min(rminsum[p],sum[p]-sum[p*2]);
	rminsum[p]=min(rminsum[p],sum[p]-sum[p*2]+rminsum[p*2]);
	maxsum[p]=maxsum[2*p];
	maxsum[p]=max(maxsum[p],maxsum[2*p+1]);
	maxsum[p]=max(maxsum[p],rmaxsum[2*p]+lmaxsum[2*p+1]);
	minsum[p]=minsum[2*p];
	minsum[p]=min(minsum[p],minsum[2*p+1]);
	minsum[p]=min(minsum[p],rminsum[2*p]+lminsum[2*p+1]);
}
int main()
{
	int n,m,x,y;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&x);
		insert(1,1,n,i,x);
	//	printf("%d\n",sum[1]);
		a[i]=x;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		insert(1,1,n,x,y);
		a[x]=y;
	//	printf("%d %d %d\n",maxsum[1],sum[1],minsum[1]);
		printf("%d\n",max(maxsum[1],sum[1]-minsum[1]));
	}
	return 0;
}
