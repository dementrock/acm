#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 8001
struct segment
{
	int y1,y2,x;
} seg[MAXN];
int n,c[4*MAXN],tot,vis[MAXN];
short map[MAXN][1001];
inline int max(int a, int b){
	return a>b?a:b;
}
int cmp(const void *a, const void *b){
	segment *x=(segment*)a,*y=(segment*)b;
	return x->x-y->x;
}
void insert(int p, int left, int right, int y1, int y2, int color){
	if(left==y1&&right==y2||left==right){
		c[p]=color;
		return;
	}
	if(c[p]) c[p*2]=c[p*2+1]=c[p];
	c[p]=0;
	int mid=left+right>>1;
	if(y2<=mid)
		insert(p*2,left,mid,y1,y2,color);
	else if(y1>mid)
		insert(p*2+1,mid+1,right,y1,y2,color);
	else{
		insert(p*2,left,mid,y1,mid,color);
		insert(p*2+1,mid+1,right,mid+1,right,color);
	}
}
void dealwith(int p, int left, int right, int y1, int y2, int id){
	if(c[p]){
		if(!vis[c[p]]){
			map[id][++map[id][0]]=c[p];
			map[c[p]][++map[c[p]][0]]=id;
			vis[c[p]]=1;
		}
		return;
	}
	if(left==right) return;
	int mid=left+right>>1;
	if(y2<=mid)
		dealwith(p*2,left,mid,y1,y2,id);
	else if(y1>mid)
		dealwith(p*2+1,mid+1,right,y1,y2,id);
	else{
		dealwith(p*2,left,mid,y1,mid,id);
		dealwith(p*2+1,mid+1,right,mid+1,right,id);
	}
}
void print()
{
	int ans=0,x,y,z;
	for(int i=1;i<=n;++i){
		x=i;
	//	printf("%d: ",i);
		for(int j=1;j<=map[i][0];++j){
		//	printf("%d ",map[i][j]);
			y=map[i][j];
			for(int k=1;k<=map[y][0];++k){
				z=map[y][k];
				if(z!=x){
					for(int t=1;t<=map[z][0];++t){
						if(map[z][t]==x){
			///			printf("%d %d %d\n",x,y,z);
							++ans;
							break;
						}
					}
				}
			}
		}
	//	printf("\n");
	}
	printf("%d\n",ans/6);
}
int main()
{
//	printf("%d\n%d\n",sizeof(vis)/1024/1024,sizeof(map)/1024/1024);
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d%d%d",&seg[i].y1,&seg[i].y2,&seg[i].x);
			seg[i].y1<<=1;
			seg[i].y2<<=1;
			seg[i].x<<=1;
			tot=max(tot,seg[i].y2);
		}
		qsort(seg+1,n,sizeof(seg[0]),cmp);
	//	for(int i=1;i<=n;++i)
	//		printf("%d %d %d %d\n",i,seg[i].x,seg[i].y1,seg[i].y2);
		int i=1,j;
		while(i<=n){
		//	printf("%d\n",i);
			for(j=i;j<=n&&seg[j].x==seg[i].x;++j){
				memset(vis,0,sizeof(vis));
				dealwith(1,1,tot,seg[j].y1,seg[j].y2,j);
			}
		//	while(1);
			for(j=i;j<=n&&seg[j].x==seg[i].x;++j)
				insert(1,1,tot,seg[j].y1,seg[j].y2,j);
			i=j;
		}
		print();
	}
	return 0;
}
