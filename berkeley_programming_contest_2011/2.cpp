#include "contest.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXN 10001
using namespace std;

struct point {
    double x, y;
} p[MAXN];

int bot, top, n, ans[3 * MAXN];

inline double dis(point a, point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int cmp(const void *a, const void *b) {
    point *a1 = (point *)a, *b1 = (point *)b;
    if (a1 -> y != b1 -> y) {
        return a1 -> y - b1 -> y;
    } else {
        return a1 -> x - b1 -> x;
    }
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

int input () {
    char inputline[1000001] = {};
    n = 1;
    gets(inputline);
    if (!strlen(inputline)) {
        return 0;
    }
    stringstream str(inputline);
    while (str >> p[n].x >> p[n].y) {
        ++n;
    }
    --n;
    return 1;
}

void calc(int cur_case) {
    if (n == 1) {
        printf("Set #%d: Diameter is %.2lf\n", cur_case, 0.0);
        return;
    } else if (n == 2) {
        printf("Set #%d: Diameter is %.2lf\n", cur_case, dis(p[1], p[2]));
        return;
    }
    double maxdis = -1;
    calc_convex();
    for (int i = bot + 1; i <= top - 1; ++i) {
        for (int j = i + 1; j <= top - 1; ++j) {
            if (dis(p[ans[i]], p[ans[j]]) > maxdis) {
                maxdis = dis(p[ans[i]], p[ans[j]]);
            }
        }
    }
    printf("Set #%d: Diameter is %.2lf\n", cur_case, maxdis);
}

int main(){
    //freopen("test.in", "r", stdin);
    int cases = 0;
    while (input()) {
        calc(++cases);
    }
    exit(0);
}
