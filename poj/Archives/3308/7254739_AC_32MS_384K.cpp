#include<iostream>
using namespace std;
#include<cmath>
#define MAX 110
struct Node
{
double c,f;
}map[MAX][MAX];
int pre[MAX];
int que[MAX];
int s,t;
inline bool findroad()
{
int i,cur,head,tail;
memset(pre,-1,sizeof(pre));
pre[s] = s;
    head = 0;
tail = 1;
que[head] = s;
while(head < tail)
{
   cur = que[head++];
   for(i = 0; i <= t; i++)
   {
    if(pre[i] == -1 && map[cur][i].c - map[cur][i].f > 0)
    {
     que[tail++] = i;
     pre[i] = cur;
     if(i == t)
      return 1;
    }
   }
}
return 0;
}
inline double maxflow()
{
double max_flow = 0,min;
int i;
while(findroad())
{
   min = 100000000;
   for(i = t; i != s; i = pre[i])
   {
    if(map[pre[i]][i].c - map[pre[i]][i].f < min)
     min = map[pre[i]][i].c - map[pre[i]][i].f;
   }
   for(i = t; i != s; i = pre[i])
   {
    map[pre[i]][i].f += min;
    map[i][pre[i]].f -= min;
   }
   max_flow += min;
}
return max_flow;
}
int main()
{
int i,j,n,m,l,r,cc,w;
double c;
scanf("%d",&w);
    while(w--)
{
   memset(map,0,sizeof(map));
   scanf("%d %d %d",&n,&m,&l);
   s = 0 ; t = n + m + 1;
   for(i = 1 ; i <= n; i ++)
   {
            scanf("%lf",&c);
    map[s][i].c = log(c);
   }
   for(i = 1; i <= m; i ++)
   {
    scanf("%lf",&c);
    map[i+n][t].c = log(c);
   }
   for(i = 1; i <= l; i ++)
   {
    scanf("%d %d",&r,&cc);
    map[r][n+cc].c = 10000000;
   }
   printf("%.4lf\n",exp(maxflow()));
}
}
