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
void Union(int a, int b)
{
	int x=getfather(a),y=getfather(b);
	father[x]=y;
}
void work()
{
	memset(mint,0,sizeof(mint));
	int minspan=0,tminspan=0;
	for(int i=1;i<=m;++i) if(getfather(edge[i].x)!=getfather(edge[i].y))
	{
		mint[++mint[0]]=i;
		minspan+=edge[i].z;
		Union(edge[i].x,edge[i].y);
	}
	for(int i=2;i<=n;++i) if(getfather(i)!=getfather(1))
	{
		printf("%d\n",minspan);
		return;
	}
	printf("%d\n",minspan);
	memset(canuse,true,sizeof(canuse));
	for(int i=1;i<=mint[0];++i)
	{
		tminspan=0;
		canuse[mint[i]]=false;
		for(int j=1;j<=n;++j) father[j]=j;
		for(int j=1;j<=m;++j) if(canuse[j]) if(getfather(edge[j].x)!=getfather(edge[j].y))
		{
			tminspan+=edge[j].z;
			Union(edge[j].x,edge[j].y);
		}
		for(int j=2;j<=n;++j) if(getfather(j)!=getfather(1)) continue;
		printf("%d %d %d %d\n",tminspan,edge[mint[i]].x,edge[mint[i]].y,edge[mint[i]].z);
		if(tminspan==minspan)
		{
			printf("Not Unique!\n");
			return;
		}
		canuse[mint[i]]=true;
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
