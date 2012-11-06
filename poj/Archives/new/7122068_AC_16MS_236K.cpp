#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 10001
struct intv
{
	int x1,x2;
} interval[MAXN];
int n,h,tr,r,c[MAXN*8];
void swap(int &a, int &b)
{
	int x=a;
	a=b;
	b=x;
}
int cmp(const void *a, const void *b)
{
	intv *x=(intv *)a,*y=(intv *)b;
	if(x->x1==y->x1)
		return x->x2-y->x2;
	else
		return x->x1-y->x1;
}
void insert(int p, int left, int right, int x1, int x2)
{
	if(left==x1&&right==x2||left==right)
	{
		--c[p];
		return;
	}
	int mid=left+right>>1;
	if(x2<=mid)
		insert(p*2,left,mid,x1,x2);
	else if(x1>mid)
		insert(p*2+1,mid+1,right,x1,x2);
	else{
		insert(p*2,left,mid,x1,mid);
		insert(p*2+1,mid+1,right,mid+1,x2);
	}
}
int get(int p, int left, int right, int x)
{
	if(left==right)
		return c[p];
	int mid=left+right>>1;
	if(x<=mid)
		return c[p]+get(p*2,left,mid,x);
	else
		return c[p]+get(p*2+1,mid+1,right,x);
}
int main()
{
	int a,b;
	scanf("%d%d%d%d",&n,&h,&h,&tr);
	for(int i=1;i<=tr;++i)
	{
		scanf("%d%d",&a,&b);
		if(a>b) swap(a,b);
		if(a>b-2) continue;
		interval[++r].x1=a;
		interval[r].x2=b;
	}
	qsort(interval+1,r,sizeof(interval[0]),cmp);
	interval[0].x1=interval[0].x2=-1;
	for(int i=1;i<=r;++i)
		if(interval[i].x1!=interval[i-1].x1||interval[i].x2!=interval[i-1].x2)
			insert(1,1,n,interval[i].x1+1,interval[i].x2-1);
	for(int i=1;i<=n;++i)
		printf("%d\n",h+get(1,1,n,i));
	return 0;
}
