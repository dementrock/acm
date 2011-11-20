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

void insert(int p, int left, int right, int x1, int x2, int color)
{
	if(x1==left&&x2==right)
	{
		if(!c[p]){
			c[p]=color;
			appear[color]=1;
		}
	//	printf("%d %d %d\n",left,right,c[p]);
		return;
	}
	int mid=left+right>>1;
	if(x1<=mid)
		insert(p*2,left,mid,x1,mid,color);
	if(x2>=mid+1)
		insert(p*2+1,mid+1,right,mid+1,x2,color);
}

int cmp(const void *a, const void *b){
	pix *x=(pix*)a;
	pix *y=(pix*)b;
	return x->x-y->x;
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
		//	tot=max(tot,seg[i].x1);
		//	tot=max(tot,seg[i].x2);
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
		for(int i=n;i>=1;--i)
			insert(1,1,tot,seg[i].x1,seg[i].x2,i);
		for(int i=1;i<=n;++i)
			ans+=appear[i];
		printf("%d\n",ans);
	}
	return 0;
}
