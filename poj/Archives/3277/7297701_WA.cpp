#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 100001
#define MAXP 200001
#define MAXT 400001
struct segment{
	int x,y,h;
} seg[MAXN];
struct Point{
	int x,id1,id2;
} point[MAXP];
int change[MAXP],N,pnum,tot;
long long area[MAXT];
int cmp(const void *a, const void *b){
	segment *x=(segment*)a, *y=(segment*)b;
	return x->h-y->h;
}
int cmp1(const void *a, const void *b){
	Point *x=(Point*)a, *y=(Point*)b;
	return x->x-y->x;
}
void add(int p, int l, int r, int x, int y, int h){
	if(l==x&&r==y||r-l<=1){
		area[p]=(change[y]-change[x])*h;
		//printf("%d %d %d-- %d %d %d %d\n",p,area[p],h,x,y,change[x],change[y]);
		return;
	}
	int m=l+r>>1;
	if(y<=m){
		add(p*2,l,m,x,y,h);
	}else if(x>=m){
		add(p*2+1,m,r,x,y,h);
	}else{
		add(p*2,l,m,x,m,h);
		add(p*2+1,m,r,m,y,h);
	}
	area[p]=area[p*2]+area[p*2+1];
}
int main(){
	scanf("%d\n",&N);
	for(int i=1;i<=N;++i){
		scanf("%d %d %d\n",&seg[i].x,&seg[i].y,&seg[i].h);
		point[++pnum].x=seg[i].x;
		point[pnum].id1=i;
		point[pnum].id2=1;
		point[++pnum].x=seg[i].y;
		point[pnum].id1=i;
		point[pnum].id2=2;
	}
	qsort(point+1,pnum,sizeof(point[0]),cmp1);
	for(int i=1;i<=pnum;++i){
		if(point[i].x!=point[i-1].x){
			++tot;
			change[tot]=point[i].x;
		//	printf("%d %d\n",tot,change[tot]);
		}
		if(point[i].id2==1){
			seg[point[i].id1].x=tot;
		}else{
			seg[point[i].id1].y=tot;
		}
	}
	qsort(seg+1,N,sizeof(seg[0]),cmp);
	for(int i=1;i<=N;++i){
		add(1,1,tot,seg[i].x,seg[i].y,seg[i].h);
	}
	printf("%lld\n",area[1]);
	return 0;
}
