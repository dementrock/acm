#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAXN 1000004
#define INF 0x7fffffff

int dig[MAXN];           //原数组
int digi[MAXN];
int d[MAXN];           //离散化以后，存放的数
int cnt[MAXN];           //cnt[i]表示 出现d[i]这个值的位置
int t;             //t是d数组的长度

int comp(const void* a,const void* b)
{
return *(int*)a-*(int*)b;
}

int BinSearch(int a)
{
int left,right,mid;
left=0;
right=t-1;
while(left<=right)
{
   mid=(left+right)/2;
   if( d[mid]==a )
    return mid;
   if( d[mid]>a )
    right=mid-1;
   else
    left=mid+1;
}
return -1;
}

int main()
{
int n;
int i,j;
while(scanf("%d",&n)!=EOF)
{
   for(i=0;i<n;i++)
   { scanf("%d",&dig[i]);
    digi[i]=dig[i];
   }
   qsort(dig,n,sizeof(dig[0]),comp);     //排序
   int tmp;
   tmp=-1;
   t=0;
   for(i=0;i<n;i++)
   {
    if( tmp!=dig[i] )
    {
     d[t]=dig[i];
     tmp=d[t++];
    }
   }            //离散化
   memset(cnt,-1,sizeof(cnt));
   int count=0;
   int min,ttt;
   int max=INF;

   for(i=0;i<n;i++)
   {
    tmp=BinSearch(digi[i]);

    if( cnt[tmp]==-1 )
    { cnt[tmp]=i;        //i是当前的位置
     count++;
    }
    else
     cnt[tmp]=i;

    if( count ==t )
    {
     min=INF;
     for(j=0;j<t;j++)
      if( cnt[j]<min )
      {
       min=cnt[j];
       ttt=j;
      }
    
     if( i-min<max )
      max=i-min;
     cnt[ttt]=-1;
     count--;
    }
   }

   printf("%d\n",max+1);
}
return 0;
}
