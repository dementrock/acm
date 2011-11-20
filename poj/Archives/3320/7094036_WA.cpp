#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 2000001
int ta[MAXN],a[MAXN],n,id[MAXN],maxnum,h[MAXN],size,ans=999999999;
void swap(int &a, int &b){int x=a;a=b;b=x;}
inline int getmin(){return h[1];}
inline int min(int a, int b){return a>b?b:a;}
void heapdown(int now)
{
	int t=now;
	while(1)
	{
		int l=t<<1,r=(t<<1)+1,heapmax=t;
		if(r<=size&&h[r]<h[heapmax]) heapmax=r;
		if(l<=size&&h[l]<h[heapmax]) heapmax=l;
		if(heapmax==t) return;
		swap(h[heapmax],h[t]);
		swap(id[heapmax],id[t]);
		t=heapmax;
	}
}
void heapup(int now)
{
	int t=now;
	while(t>1&&h[t]<h[t>>1])
	{
		swap(h[t],h[t>>1]);
		swap(id[a[t]],id[a[t>>1]]);
		t=t>>1;
	}
}
void change(int now, int key)
{
	h[now]=key;
	heapdown(now);
}
void insert(int key)
{
	h[++size]=key;
	heapup(size);
}
void quicksort(int left, int right)
{
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(ta[i],ta[right]);
	swap(id[i],id[right]);
	for(j=left,i=left-1;j<right;++j)
		if(ta[j]<ta[right])
		{
			swap(ta[++i],ta[j]);
			swap(id[i],id[j]);
		}
	swap(ta[++i],ta[right]);
	swap(id[i],id[right]);
	quicksort(left,i-1);
	quicksort(i+1,right);
}
void init()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&ta[i]);
		id[i]=i;
	}
	quicksort(1,n);
	ta[0]=-1;
	for(int i=1;i<=n;++i)
		if(ta[i]==ta[i-1])
			a[id[i]]=a[id[i-1]];
		else a[id[i]]=++maxnum;
}
void work()
{
	memset(id,0,sizeof(id));
	for(int i=1;i<=n;++i)
	{
		if(id[a[i]])
			change(id[a[i]],i);
		else
		{
			id[a[i]]=size+1;
			insert(i);
		}
		if(size==maxnum) ans=min(ans,i-getmin()+1);
	//	for(int j=1;j<=size;++j) printf("%d ",h[j]);
	//	printf("\n");
	//	for(int j=1;j<=maxnum;++j) printf("%d ",id[j]);
	//	printf("\n");
	}
	printf("%d\n",ans);
}
int main()
{
	init();
	work();
	return 0;
}
