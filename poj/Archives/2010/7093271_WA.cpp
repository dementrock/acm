#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 200001
struct Cow
{
	int score,aid;
} cow[MAXN];
int n,c,f,h[MAXN],size,sum1[MAXN],sum2[MAXN],ans;
inline int max(int a, int b){return a>b?a:b;}
void swap(Cow &a, Cow &b){Cow x=a;a=b;b=x;}
void swap(int &a, int &b){int x=a;a=b;b=x;}
void quicksort(Cow a[], int left, int right){
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(a[i],a[right]);
	for(j=left,i=left-1;j<right;++j) 
		if(a[j].score<a[right].score)
			swap(a[++i],a[j]);
	swap(a[++i],a[right]);
	quicksort(a,left,i-1);
	quicksort(a,i+1,right);
}
void init()
{
	scanf("%d%d%d",&n,&c,&f);
	for(int i=1;i<=c;++i)
		scanf("%d%d",&cow[i].score,&cow[i].aid);
}
void heapup(int now)
{
	int t=now;
	while(t&&h[t]>h[t>>1])
	{
		swap(h[t],h[t>>1]);
		t=t>>1;
	}
}
void heapdown(int now)
{
	int t=now;
	while(t<=size)
	{
		int l=t<<1,r=(t<<1)+1,heapmax=t;
		if(l>size) return;
		if(r<=size&&h[r]>h[heapmax]) heapmax=r;
		if(l<=size&&h[l]>h[heapmax]) heapmax=l;
		if(heapmax==t) return;
		swap(h[heapmax],h[t]);
		t=heapmax;
	}
}
void insert(int key)
{
	h[++size]=key;
	heapup(size);
}
inline int maxinum(){return h[1];}
int extmax()
{
	int ret=h[1];
	h[1]=h[size--];
	heapdown(1);
	return ret;
}
void work()
{
	if(n>c){
		printf("-1\n");
		return;
	}
	quicksort(cow,1,c);
//	for(int i=1;i<=c;++i) printf("%d %d %d\n",i,cow[i].score,cow[i].aid);
	for(int i=1;i<=n/2;++i){
		insert(cow[i].aid);
		sum1[n/2+1]+=cow[i].aid;
	}
	for(int i=n/2+2;i<=c-n/2;++i){
		sum1[i]=sum1[i-1];
		if(maxinum()>cow[i].aid){
			sum1[i]=sum1[i-1]-maxinum()+cow[i].aid;
			extmax();
			insert(cow[i].aid);
		}
	}
	memset(h,0,sizeof(h));
	for(int i=c-n/2+1;i<=c;++i){
		insert(cow[i].aid);
		sum2[c-n/2]+=cow[i].aid;
	}
	for(int i=c-n/2-1;i>=n/2+1;--i){
		sum2[i]=sum2[i+1];
		if(maxinum()>cow[i].aid){
			sum2[i]=sum2[i+1]-maxinum()+cow[i].aid;
			extmax();
			insert(cow[i].aid);
		}
	}
	for(int i=n/2+1;i<=c-n/2;++i){
	//	printf("%d\n",sum1[i]+sum2[i]);
		if(sum1[i]+sum2[i]+cow[i].aid<=f)
			ans=max(ans,cow[i].score);
	}
	if(ans) printf("%d\n",ans);
	else printf("-1\n");
}
int main()
{
	init();
	work();
	return 0;
}
