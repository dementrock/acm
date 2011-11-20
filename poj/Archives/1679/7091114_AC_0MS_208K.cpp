#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct
{
int w;
int x;
int y;
}a[10000];
int r[105],ms,sms;
int used[105];          //记录最小生成树的每一条边
int cmp(const void *a,const void *b)
{
return *(int *)a-*(int *)b;
}
int find(int x)
{
int t=x;
while (r[x]!=x)
   x=r[x];
r[t]=x;
return x;
}
int bing (int x,int y)
{
x=find(x);
y=find(y);
if (x==y) return 0;
r[x]=y;
return 1;
}
int main ()
{
int i,j,t,n,m,p,flog;
scanf("%d",&t);
while (t--)
{
   scanf("%d %d",&n,&m);
   for (i=0;i<105;i++)
    r[i]=i;
   for (i=0;i<m;i++)
    scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].w);
   qsort(a,m,sizeof(a[0]),cmp);
   ms=0;p=1;i=0;         //建最小生成树
   while (p<n && i<m)
   {
    if (bing (a[i].x,a[i].y))
    {
     ms+=a[i].w;
     used[p]=i;
     p++;
    }
    i++;
   }
   flog=0;
   for (j=1;j<n;j++)          //每删掉原来最小生成树的一条边，就重建一棵树
   {
    for (i=0;i<105;i++)
     r[i]=i;
    sms=0;p=n-1;i=0;
    while (p && i<m)
    {
     if (i!=used[j] &&bing (a[i].x,a[i].y))
     {
      sms+=a[i].w;
      p--;
     }
     i++;
    }
    if (sms==ms && !p) {flog=1;break;}
   }
   if (flog) printf ("Not Unique!\n");
   else printf ("%d\n",ms);
}
return 0;}
