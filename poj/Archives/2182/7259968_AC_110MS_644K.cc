#include<stdio.h>
struct segtree
{
	int l,r,cnt;
} t[20001];
int n,a[8001],ans[8001];
void init()
{
	scanf("%d",&n);
	a[1]=0;
	for(int i=2;i<=n;++i) scanf("%d",&a[i]);
}
void build(int l, int r, int id)
{
	t[id].l=l;
	t[id].r=r;
	t[id].cnt=r-l+1;
	if(l<r)
	{
		build(l,l+r>>1,id<<1);
		build((l+r>>1)+1,r,(id<<1)+1);
	}
}
int del(int now, int x)
{
	if(t[x].l==t[x].r)
	{
		t[x].cnt=0;
		return t[x].l;
	}
	--t[x].cnt;
	if(now<=t[x<<1].cnt)
		return del(now,x<<1);
	else return del(now-t[x<<1].cnt,(x<<1)+1);
}
void work()
{
	build(1,n,1);
	for(int i=n;i>=1;--i)
		ans[i]=del(a[i]+1,1);
	for(int i=1;i<=n;++i)
		printf("%d\n",ans[i]);
}
int main()
{
	init();
	work();
	return 0;
}
