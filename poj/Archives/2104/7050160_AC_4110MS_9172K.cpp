#include<stdio.h>
#include<stdlib.h>
#define max(a,b) a>b?a:b
struct news
{
	int id,num;
} b[100001];
int maxdep,sortarr[21][100001],
n,m,a[100001],l,r,loc[100001],init[100001];
void mergesort(int left, int right, int depth)
{
	maxdep=max(maxdep,depth);
	if(left==right)
		sortarr[depth][left]=a[left];
	else
	{
		int mid=left+right>>1;
		mergesort(left,mid,depth+1);
		mergesort(mid+1,right,depth+1);
		int pos1=left,pos2=mid+1,pos=left-1;
		while(pos1<=mid||pos2<=right)
			if(pos1>mid||(pos2<=right&&sortarr[depth+1][pos1]>sortarr[depth+1][pos2]))
				sortarr[depth][++pos]=sortarr[depth+1][pos2++];
			else
				sortarr[depth][++pos]=sortarr[depth+1][pos1++];
	}
}
int bifind(int left, int right, int depth, int k)
{
	
	int l=left,r=right,m;
	while(r-l>1)
	{
		m=l+r>>1;
		if(sortarr[depth][m]>k) r=m;
		else l=m;
	}
	while(sortarr[depth][l]<=k&&l<=right) ++l;
	--l;
//	printf("%d %d %d %d--%d\n",left,right,depth,k,l-left+1);
	return l-left+1;
}
int work(int left, int right, int depth, int k)
{
//	printf("work:%d %d %d %d %d %d\n",l,r,left,right,depth,k);
	if(l<=left&&right<=r)
		return bifind(left,right,depth,k);
	int ans=0;
	int mid=left+right>>1;
	if(mid>=l)
		ans+=work(left,mid,depth+1,k);
	if(r>=mid+1)
		ans+=work(mid+1,right,depth+1,k);
	return ans;
}
int dealwith(int left, int right, int k)
{
	int l=1,r=n,minc,ll,rr;
	while(r-l>1)
	{
		int m=l+r>>1,now=work(left,right,1,m);
	//	printf("%d %d||||%d %d\n",l,r,m,now);
		if(now<=k) l=m;
		else r=m;
	}
	rr=r;
	l=1,r=n;
	while(r-l>1)
	{
		int m=l+r>>1,now=work(left,right,1,m);
	//	printf("%d %d||||%d %d\n",l,r,m,now);
		if(now<k) l=m;
		else r=m;
	}
	ll=l;
	for(int i=ll;i<=rr;++i)
	{
//		printf("%d %d %d %d:%d\n",left,right,k,i,work(left,right,1,i));
		if(work(left,right,1,i)==k&&left<=loc[i]&&loc[i]<=right)
			return init[i];
	}
}
void swap(news *a, news *b){news x=*a;*a=*b;*b=x;}
void quicksort(int left, int right){
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(&b[i],&b[right]);
	for(j=left,i=left-1;j<right;++j)
		if(b[j].num<b[right].num) swap(&b[++i],&b[j]);
	swap(&b[++i],&b[right]);
	quicksort(left,i-1);
	quicksort(i+1,right);
}
int main()
{
	int c;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		b[i].id=i;b[i].num=a[i];
	}
	quicksort(1,n);
	for(int i=1;i<=n;++i)
	{
		init[i]=a[b[i].id];
		a[b[i].id]=i;
		loc[i]=b[i].id;
	}
	mergesort(1,n,1);
	for(int t=1;t<=m;++t)
	{
		scanf("%d%d%d",&l,&r,&c);
		printf("%d\n",dealwith(1,n,c));
	}
	return 0;
}
