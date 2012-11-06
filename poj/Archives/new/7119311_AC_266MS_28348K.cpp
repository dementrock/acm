#include<stdio.h>
#include<string.h>
#define MAXN 200010
struct pix
{
	long long x,y,c;
} p[2*MAXN];
long long tY[2*MAXN],Y[2*MAXN],sum[4*MAXN],maxsum[4*MAXN],n,w,h,np,nty,ny,ans;
inline long long max(long long a, long long b)
{
	return a>b?a:b;
}
void swap(pix &a, pix &b)
{
	pix x=a;
	a=b;
	b=x;
}
void swap(long long &a, long long &b)
{
	long long x=a;
	a=b;
	b=x;
}
void quicksort(pix p[], int left, int right)
{
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(p[i],p[right]);
	for(j=left,i=left-1;j<right;++j)
		if(p[j].x<p[right].x)
			swap(p[j],p[++i]);
	swap(p[++i],p[right]);
	quicksort(p,left,i-1);
	quicksort(p,i+1,right);
}
void quicksort(long long p[], int left, int right)
{
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(p[i],p[right]);
	for(j=left,i=left-1;j<right;++j)
		if(p[j]<p[right])
			swap(p[j],p[++i]);
	swap(p[++i],p[right]);
	quicksort(p,left,i-1);
	quicksort(p,i+1,right);
}
void insert(int now, int left, int right, int x, long long c)
{
	int mid=left+right>>1;
	if(x!=mid)
	{
		if(x<mid)
			insert(now*2,left,mid-1,x,c);
		else
			insert(now*2+1,mid+1,right,x,c);
	}
	sum[now]+=c;
	maxsum[now]=maxsum[now*2];
	maxsum[now]=max(maxsum[now],sum[now]-sum[now*2+1]);
	maxsum[now]=max(maxsum[now],sum[now]-sum[now*2+1]+maxsum[now*2+1]);
}
int find(long long x)
{
	int left=1,right=ny;
	while(left<=right)
	{
		int mid=left+right>>1;
		if(Y[mid]==x) return mid;
		if(Y[mid]<x) left=mid+1;
		else right=mid-1;
	}
	return left;
}
int main()
{
	long long x,y,c;
	while(~scanf("%I64d%I64d%I64d",&n,&w,&h))
	{
		np=nty=ny=ans=0;
		memset(p,0,sizeof(p));
		memset(sum,0,sizeof(sum));
		memset(Y,0,sizeof(Y));
		memset(tY,0,sizeof(tY));
		memset(maxsum,0,sizeof(maxsum));
		--w,--h;
		for(int i=1;i<=n;++i)
		{
			scanf("%I64d%I64d%I64d",&x,&y,&c);
			p[++np].x=x;
			p[np].y=y;
			p[np].c=c;
			p[++np].x=x;
			p[np].y=y+h+1;
			p[np].c=-c;
			tY[++nty]=y;
			tY[++nty]=y+h+1;
		}
		quicksort(p,1,np);
		quicksort(tY,1,nty);
		for(int i=1;i<=nty;++i)
			if(i==1||tY[i]!=tY[i-1])
				Y[++ny]=tY[i];
		int t=1,s=1;
       // for(int i=1;i<=np;++i) printf("%d %d %d\n",p[i].x, p[i].y, p[i].c);
		while(t<=np)
		{
			long long tx=p[t].x;
			while(s<=np&&tx-p[s].x>w)
				insert(1,1,ny,find(p[s].y),-p[s++].c);
			while(t<=np&&p[t].x==tx)
				insert(1,1,ny,find(p[t].y),p[t++].c);
			ans=max(ans,maxsum[1]);
	//		printf("%d %d\n",s,t);
		}
		printf("%I64d\n",ans);
	}
}
