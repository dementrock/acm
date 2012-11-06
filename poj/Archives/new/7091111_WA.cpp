#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;
const int MAXV=105;
const int MAXE=5465;
const int INF=0x7fffffff;
int set[MAXV];
int rank[MAXV];
int num;//记录最小生成树边的个数
int st,ed;
typedef struct Edge
{
int st;
int ed;
int distance;
}Edge;
Edge edge[MAXE];
Edge edge1[MAXE];
/*下面三个函数是求并查集的函数!*/
//第一函数是初始化
void Make_Set(int x)
{
set[x]=x;
rank[x]=0;
}
//返回包含x的集合中的一个代表元素
int Find_Set(int x)
{
if(x!=set[x])
   set[x]=Find_Set(set[x]);
return set[x];
}
//实现树与树的合并
void Union(int x,int y)
{
x=Find_Set(x);
y=Find_Set(y);
if(rank[x]>rank[y])
   set[y]=x;
else
{
   set[x]=y;
   if(rank[x]==rank[y])
    rank[y]++;
}
}
bool cmp(Edge a,Edge b)
{
return a.distance<b.distance;
}
/*关键函数-Kruskal算法的实现!*/
int Kruskal(int v,int e)
{
int i;
int sum=0;
for(i=1;i<=v;i++)
   Make_Set(i);//每个点构成一个树也即一个集合
sort(edge+1,edge+e+1,cmp);//将边按照权值非降序排序
for(i=1;i<=e;i++)
   if(Find_Set(edge[i].st)!=Find_Set(edge[i].ed))
   {//如果是安全边就加sum中去
    sum+=edge[i].distance;
    //并将包含这两棵树的集合合并
    Union(edge[i].st,edge[i].ed);
    edge1[++num]=edge[i];
   }
return sum;
}
int Kruskal1(int v,int e)
{
int i;
int sum=0;
for(i=1;i<=v;i++)
   Make_Set(i);//每个点构成一个树也即一个集合
sort(edge+1,edge+e+1,cmp);//将边按照权值非降序排序
for(i=1;i<=e;i++)
   if(Find_Set(edge[i].st)!=Find_Set(edge[i].ed))
   {//如果是安全边就加sum中去
     if(edge[i].st==st&&edge[i].ed==ed)
     {continue;}
     if(edge[i].st==ed&&edge[i].ed==st)
     {continue;}
    sum+=edge[i].distance;
    //并将包含这两棵树的集合合并
    Union(edge[i].st,edge[i].ed);
   }
return sum;
}
bool Judge(int V)
{
     int i;
     for(i=1;i<=V-1;i++)
        if(Find_Set(i)!=Find_Set(i+1))
            return false;
     return true;
}
int main()
{
	
    int i,V,E,T,min,sum;
    scanf("%d",&T);
    while(T--)
    {
       scanf("%d%d",&V,&E);
       for(i=1;i<=E;i++)
         scanf("%d%d%d",&edge[i].st,&edge[i].ed,&edge[i].distance);
       num=0;
       min=INF;
       sum=Kruskal(V,E);
       //printf("num=%d\n",num);
       for(i=1;i<=num;i++)
       {
          st=edge1[i].st;
          ed=edge1[i].ed;
          int temp=Kruskal1(V,E);
          if(min>temp&&Judge(V))//一定要加一个判断！看看是不是所有的点都联通！
                 min=temp;
          if(Judge(V))printf("%d\n",temp);
       }
       printf("%d %d\n",min,sum);
       if(min==sum)
          printf("Not Unique!\n");
       else
          printf("%d\n",sum);
    }
    return 0;
}
