#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int n,q;
int ql[100001],qr[100001],a[100001],f[100001][20],num[100001],times[100001];
void init()
{
	n=0;
	scanf("%d",&n);
	memset(a,0,sizeof(a));
	memset(ql,0,sizeof(ql));
	memset(qr,0,sizeof(qr));
	memset(f,0,sizeof(f));
	memset(num,0,sizeof(num));
	memset(times,0,sizeof(times));
	if(!n)
		exit(0);
	scanf("%d",&q);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<=q;++i)
		scanf("%d%d",&ql[i],&qr[i]);
}
inline int max(int a, int b)
{
	return a>b?a:b;
}
void find(int l, int k)
{
	if(k==0){ f[l][k]=num[l];return;}
	if(!f[l][k-1]) find(l,k-1);
	if(!f[l+(1<<(k-1))][k-1]) find(l+(1<<(k-1)),k-1);
	f[l][k]=max(f[l][k-1],f[l+(1<<(k-1))][k-1]);
}
int rmq(int l, int r)
{
	if(l>=r) return 0;
	int m=(int)(log(1.0*(r-l+1))/log(2.0)),
		mr=r-(1<<m)+1;
	if(!f[l][m]) find(l,m);
	if(!f[mr][m]) find(mr,m);
	return max(f[l][m],f[mr][m]);
}
void work()
{
	num[1]=1;
	for(int i=2;i<=n;++i)
		num[i]=a[i]==a[i-1]?num[i-1]+1:1;
	times[n]=num[n];
	for(int i=n-1;i>=1;--i)
		times[i]=a[i]==a[i+1]?times[i+1]:num[i];
	for(int i=1;i<=q;++i)
	{
		int ans=0;
		ans=max(ans,times[ql[i]]-num[ql[i]]+1);
		ans=max(ans,num[qr[i]]);
		int l,r;
		for(l=ql[i];l<n&&a[l]==a[l+1];++l);
		++l;
		for(r=qr[i];r>0&&a[r]==a[r-1];--r);
		--r;
		ans=max(ans,rmq(l,r));
		printf("%d\n",ans);
	}
}
int main()
{
	while(1)
	{
		init();
		work();
	}
	return 0;
}
