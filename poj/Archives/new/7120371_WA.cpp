#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 10001
struct segment{
	int x1,x2;
} seg[MAXN];
struct pix{
	int x,id1,id2;
} p[2*MAXN];
int n,np,tot,ans,
c[8*MAXN],appear[MAXN];

inline int max(int a, int b){
	return a>b?a:b;
}

inline int min(int a, int b){
	return a<b?a:b;
}

void insert(int p, int left, int right, int x1, int x2, int color)
{
//	printf("%d %d %d %d %d %d\n",p,left,right,x1,x2,color);
	if(x1==left&&x2==right||left==right)
	{
		c[p]=color;
//		printf("%d %d %d\n",left,right,c[p]);
		return;
	}
	int x=c[p];
	if(x) c[2*p]=c[2*p+1]=x;
	c[p]=0;
	int mid=left+right>>1;
	if(mid<x1)
		insert(p*2+1,mid+1,right,x1,x2,color);
	else if(x2<=mid)
		insert(p*2,left,mid,x1,x2,color);
	else{
		insert(p*2,left,mid,x1,mid,color);
		insert(p*2+1,mid+1,right,mid+1,x2,color);
	}
}

int cmp(const void *a, const void *b){
	pix *x=(pix*)a;
	pix *y=(pix*)b;
	return x->x-y->x;
}

void check(int p, int left, int right)
{
	if(c[p]||left==right)
	{
		appear[c[p]]=1;
		return;
	}
	int mid=left+right>>1;
	check(p*2,left,mid);
	check(p*2+1,mid+1,right);
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		np=ans=tot=0;
		memset(c,0,sizeof(c));
		memset(appear,0,sizeof(appear));
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d%d",&seg[i].x1,&seg[i].x2);
			++seg[i].x2;
			p[++np].x=seg[i].x1;
			p[np].id1=i;
			p[np].id2=1;
			p[++np].x=seg[i].x2;
			p[np].id1=i;
			p[np].id2=2;
		}
		qsort(p+1,np,sizeof(p[0]),cmp);
		p[0].x=-1;
		for(int i=1;i<=np;++i){
			if(p[i].x!=p[i-1].x)
				++tot;
			if(p[i].id2==1)
				seg[p[i].id1].x1=tot;
			else
				seg[p[i].id1].x2=tot;
		}
	//	for(int i=1;i<=n;++i)
	//		printf("%d %d\n",seg[i].x1,seg[i].x2);	
		for(int i=1;i<=n;++i)
			insert(1,1,tot,seg[i].x1,seg[i].x2,i);
		check(1,1,tot);
		for(int i=1;i<=n;++i)
			ans+=appear[i];
		printf("%d\n",ans);
	}
	return 0;
}
