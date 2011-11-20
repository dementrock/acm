#include<stdio.h>
#include<math.h>
#include<string.h>
#define MAXN 1001
struct pix
{
	double x,y;
} p[MAXN];
int ans[2*MAXN+1],n;
void swap(pix &a, pix &b)
{
	pix x=a;
	a=b;
	b=x;
}
void swap(int &a, int &b)
{
	int x=a;
	a=b;
	b=x;
}
void quicksort(int left, int right)
{
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(p[i],p[right]);
	for(j=left,i=left-1;j<right;++j)
		if(p[j].y<p[right].y||p[j].y==p[right].y&&p[j].x<p[right].x)
			swap(p[++i],p[j]);
	swap(p[++i],p[right]);
	quicksort(left,i-1);
	quicksort(i+1,right);
}
void init()
{
	memset(ans,0,sizeof(ans));
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&p[i].x,&p[i].y);
}
double cross(double x1, double y1, double x2, double y2)
{
	return x1*y2-x2*y1;
}
double isleft(pix a, pix b, pix c)
{
	return cross(b.x-a.x,b.y-a.x,c.x-b.x,c.y-b.y);
}
void work()
{
	quicksort(1,n);
	int flag=1;
	for(int i=1;i<=n-2;++i)
		if(isleft(p[i],p[i+1],p[i+2])!=0)
		{
			flag=0;
			break;
		}
	if(flag)
	{
		printf("NO\n");
		return;
	}
	int bot=n,top=n+1,i;
	ans[top++]=1;
	ans[top++]=2;
	for(i=3;i<=n;++i)
	{
		if(isleft(p[ans[top-2]],p[ans[top-1]],p[i])!=0)
		{
			ans[top++]=ans[bot--]=i;
			break;
		}
		ans[top-1]=i;
	}
	if(isleft(p[ans[top-3]],p[ans[top-2]],p[ans[top-1]])<0)
		swap(ans[top-3],ans[top-2]);
	for(++i;i<=n;++i)
	{
		if(isleft(p[ans[top-2]],p[ans[top-1]],p[i])>0&&
		   isleft(p[ans[bot+1]],p[ans[bot+2]],p[i])>0)
			continue;
		while(isleft(p[ans[top-2]],p[ans[top-1]],p[i])<=0) --top;
		ans[top++]=i;
		while(isleft(p[ans[bot+1]],p[ans[bot+2]],p[i])<=0) ++bot;
		ans[bot--]=i;
	}
	for(i=bot+1;i<top-1;++i)
	{
		int cnt=0;
		for(int j=1;j<=n;++j)
			if(isleft(p[ans[i]],p[j],p[ans[i+1]])==0)
				++cnt;
		if(cnt<3)
		{
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
	return;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		init();
		work();
	}
	return 0;
}
