#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct news
{
	int x,y,z;
} edge[100001];
int father[100001],mint[100001],canuse[100001],n,m;
void swap(news &a, news &b){news x=a;a=b;b=x;}
void quicksort(news a[], int left, int right){
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(a[i],a[right]);
	for(j=left,i=left-1;j<right;++j)
		if(a[j].z<a[right].z) swap(a[++i],a[j]);
	swap(a[++i],a[right]);
	quicksort(a,left,i-1);
	quicksort(a,i+1,right);
}
int getfather(int x)
{
	if(father[x]==x) return x;
	return father[x]=getfather(father[x]);
}
bool bing(int a, int b)
{
	int x=getfather(a),y=getfather(b);
	if(x==y) return 0;
	father[x]=y;
	return 1;
}
void work()
{
	memset(mint,0,sizeof(mint));
	int minspan=0,tminspan=0;
	int p=0,i=1;
	while(p<n&&i<=m)
	{
		if(bing(edge[i].x,edge[i].y))
		{
			mint[++p]=i;
			minspan+=edge[i].z;
			canuse[p]=i;
		}
		++i;
	}
	for(int i=2;i<=n;++i) if(getfather(i)!=getfather(1))
	{
		printf("%d\n",minspan);
		return;
	}
//	printf("%d\n",minspan);
	for(int i=1;i<=p;++i)
	{
		tminspan=0;
		for(int j=1;j<=n;++j) father[j]=j;
		for(int j=1;j<=m;++j) if(j!=canuse[i]) if(bing(edge[j].x,edge[j].y))
			tminspan+=edge[j].z;
		for(int j=2;j<=n;++j) if(getfather(j)!=getfather(1)) continue;
//		printf("%d %d %d %d\n",tminspan,edge[mint[i]].x,edge[mint[i]].y,edge[mint[i]].z);
		if(tminspan==minspan)
		{
			printf("Not Unique!\n");
			return;
		}
	}
	printf("%d\n",minspan);
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		memset(father,0,sizeof(father));
		memset(edge,0,sizeof(edge));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i) father[i]=i;
		for(int i=1;i<=m;++i) scanf("%d%d%d",&edge[i].x,&edge[i].y,&edge[i].z);
		quicksort(edge,1,m);
		work();
	}
}
