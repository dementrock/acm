#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXN 50001 
struct point
{
	int x,y;
} p[MAXN];
int ans[2*MAXN+1],n, bot, top;
void swap(point &a, point &b)
{
	point x=a;
	a=b;
	b=x;
}

int cmp(const void *a, const void *b) {
    point *a1 = (point *)a, *b1 = (point *)b;
    if (a1 -> y != b1 -> y) {
        return a1 -> y - b1 -> y;
    } else {
        return a1 -> x - b1 -> x;
    }
}

void swap(int &a, int &b)
{
	int x=a;
	a=b;
	b=x;
}

void init() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
}

inline int sqrdis(point a, point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

inline double dis(point a, point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline double cross(double x1, double y1, double x2, double y2)
{
	return x1 * y2 - x2 * y1;
}
inline double isleft(point a, point b, point c)
{
	return cross(b.x - a.x, b.y - a.y, c.x - b.x, c.y - b.y);
}

void calc_convex() {
    int i;
    qsort(p + 1, n, sizeof(p[0]), cmp);
	bot=n,top=n+1;
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
}


void work()
{
    int maxdis = -1;
    calc_convex();
    for (int i = bot + 1; i <= top - 1; ++i) {
        for (int j = i + 1; j <= top - 1; ++j) {
            if (sqrdis(p[ans[i]], p[ans[j]]) > maxdis) {
                maxdis = sqrdis(p[ans[i]], p[ans[j]]);
            }
        }
    }
    printf("%d\n", maxdis);
}
int main()
{
	init();
	work();
	return 0;
}
