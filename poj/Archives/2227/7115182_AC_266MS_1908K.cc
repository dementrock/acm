#include<stdio.h>
#include<string.h>
struct heap
{
	int x,y,key;
} h[100001];
int move[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int a[301][301],size,vis[301][301],forbid[301][301],n,m;
long long ans;
void swap(heap &a, heap &b)
{
	heap x=a;
	a=b;
	b=x;
}
void heapdown(int now)
{
	while(1)
	{
		int l=now<<1,r=l+1,heapmin=now;
		if(l<=size&&h[l].key<h[heapmin].key) heapmin=l;
		if(r<=size&&h[r].key<h[heapmin].key) heapmin=r;
		if(heapmin==now) return;
		swap(h[now],h[heapmin]);
		now=heapmin;
	}
}
void heapup(int now)
{
	while(now>1&&h[now].key<h[now>>1].key)
	{
		swap(h[now],h[now>>1]);
		now>>=1;
	}
}
void extmin()
{
	h[1]=h[size--];
	heapdown(1);
//	for(int i=1;i<=size;++i) printf("%d ",h[i].key);
//	printf("\n");
}
void insert(int x, int y, int key)
{
	h[++size].x=x;
	h[size].y=y;
	h[size].key=key;
	heapup(size);
//	for(int i=1;i<=size;++i) printf("%d ",h[i].key);
//	printf("\n");
}
void dfs(int x, int y, int maxh)
{
//	printf("%d %d %d\n",x,y,maxh);
	vis[x][y]=1;
	ans+=maxh-a[x][y];
//	printf("%d\n",ans);
	for(int i=0;i<4;++i)
	{
		int nowx=x+move[i][0],nowy=y+move[i][1];
		if(1<=nowx&&nowx<=n&&1<=nowy&&nowy<=m&&!forbid[nowx][nowy]&&!vis[nowx][nowy])
		{
			if(a[nowx][nowy]<maxh)
				dfs(nowx,nowy,maxh);
			else
			{
				forbid[nowx][nowy]=1;
				insert(nowx,nowy,a[nowx][nowy]);
			}
		}
	}
}
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;++i)
	{
		forbid[i][1]=forbid[i][m]=1;
		insert(i,1,a[i][1]);
		insert(i,m,a[i][m]);
	}
	for(int i=2;i<m;++i)
	{
		forbid[1][i]=forbid[n][i]=1;
		insert(1,i,a[1][i]);
		insert(n,i,a[n][i]);
	}
	while(size)
	{
		int minh=h[1].key;
		for(int i=0;i<4;++i)
		{
			int nowx=h[1].x+move[i][0], nowy=h[1].y+move[i][1];
			if(1<=nowx&&nowx<=n&&1<=nowy&&nowy<=m&&!forbid[nowx][nowy]&&!vis[nowx][nowy])
				if(a[nowx][nowy]<minh)
					dfs(nowx,nowy,minh);
				else
				{
					forbid[nowx][nowy]=1;
					insert(nowx,nowy,a[nowx][nowy]);
				}
		}
		extmin();
	}
	printf("%I64d\n",ans);
	return 0;
}
