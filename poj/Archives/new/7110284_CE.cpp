#include<stdio.h>
#include<math.h>
#define MAXN 1001
struct point
{
	int x,y;
} p[MAXN];
double pi=3.1415926535;
int ans[2*MAXN+1],n,R;
void swap(point &a, point &b)
{
	point x=a;
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
	scanf("%d %d\n",&n,&R);
	for(int i=1;i<=n;++i)
		scanf("%d %d\n",&p[i].x,&p[i].y);
}
double dis(point a, point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double cross(double x1, double y1, double x2, double y2)
{
	return x1*y2-x2*y1;
}
double isleft(point a, point b, point c)
{
	return cross(b.x-a.x,b.y-a.y,c.x-b.x,c.y-b.y);
}
void work()
{
	int i;
	quicksort(1,n);
	int bot=n,top=n+1;
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
		if(isleft(p[ans[bot+1]],p[ans[bot+2]],p[i])>0&&
		   isleft(p[ans[top-2]],p[ans[top-1]],p[i])>0)
			continue;
		while(isleft(p[ans[top-2]],p[ans[top-1]],p[i])<=0) --top;
		ans[top++]=i;
		while(isleft(p[ans[bot+1]],p[ans[bot+2]],p[i])<=0) ++bot;
		ans[bot--]=i;
	}
	double ansdis=0;
	for(i=bot+1;i<top-1;++i)
		ansdis+=dis(p[ans[i]],p[ans[i+1]]);
	ansdis+=2*pi*R;
	printf("%.0f\n",ansdis);
}
int main()
{
	init();
	work();
	return 0;
}
