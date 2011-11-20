#include <iostream>
//#include <conio.h>
#include <queue>
using namespace std;
#define narray 240
#define karray 31
#define carray 201
const int INF = 10000000;   //不要使用0x7fffffff,否则会一直wa
int graph[narray][narray];
int dist[carray*karray];
int k,c,m;
int distnum;
int length;
int vn;
int cnt;
int capacity[narray][narray];
int src,des;

int d[narray];           //标号
int num[narray];         //num[i]表示标号为i的顶点数有多少
int pre[narray];         //记录前驱
void Floyd()
{
     int t,i,j;
     for(t=1; t<=k+c;t++)
         for(i=1;i<=k+c;i++)
              for(j=1; j<=k+c; j++)
              {
                 if(graph[i][t]<INF && graph[t][j]<INF && graph[i][j]>graph[i][t]+graph[t][j])
                     graph[i][j] = graph[i][t]+graph[t][j];
              }
                  //graph[i][j]=min(graph[i][t]+graph[t][j],graph[i][j]);

}
void init(int src,int des)             
{
     int i,j;
     queue<int> myqueue;
     myqueue.push(des);
     memset(num,0,sizeof(num));
     for(i=0;i<vn;++i)     
        d[i] = INF;
     d[des] = 0;            
     num[0] = 1;
     int frontint;
     while(!myqueue.empty()) 
     {
         frontint = myqueue.front();myqueue.pop();
         for(i=0;i<vn;++i)
         {
             if(d[i]>=vn && capacity[i][frontint]>0)  
             {
                 d[i] = d[frontint]+1;
                 myqueue.push(i); 
                 num[d[i]]++;    
             }                 
         }
     }
}
int findarc(int t)             
{
    int i,j;
    for(i=0;i<vn;++i)
    {
        if(capacity[t][i]>0 && d[t]==d[i]+1) return i;
    }
    return -1;
}
int relabel(int t)             
{
    int i,j;
    int mm = INF;
    for(i=0;i<vn;++i)
    {
        if(capacity[t][i]>0) mm = min(mm,d[i]+1);
    }
    return mm==INF?vn:mm;
}
int maxFlow(int src,int des)
{
    int sumflow = 0;
    int delta;
    int i=src;     
    int j;
    memset(pre,-1,sizeof(pre));   
    while(d[src]<vn)
    {
       j = findarc(i);
       if(j>=0)
       {
           pre[j] = i;
           i = j;          
           if(i==des)        
           {
               delta = INF;
               for (i=des;i!=src;i=pre[i]) delta=min(delta,capacity[pre[i]][i]);   
               for (i=des;i!=src;i=pre[i]) capacity[pre[i]][i] -= delta, capacity[i][pre[i]] += delta;
               sumflow += delta;
           }
       }
       else
       {
           int x = relabel(i);
           num[x]++;
           num[d[i]]--;
           if(num[d[i]]==0) return sumflow;    
           d[i] = x;
           if(i!=src) i =pre[i];          
       }
    }
    return sumflow;
}  

bool build()
{
     int i,j;
     memset(capacity,0,sizeof(capacity));
     for(i=1;i<=k;++i)
     {
         capacity[src][i]= m;
     }              
     for(i=k+1;i<=k+c;++i)
     {
         capacity[i][des] = 1;
     }      
     for(i=1;i<=k;++i)
     {
         for(j=k+1;j<=k+c;++j)
         {
             if(graph[i][j]<=length)
                capacity[i][j] =1;
             else
                capacity[i][j] =0;
         }
     }
     init(src,des);
     if(maxFlow(src,des)>=c) return true;
     else return false;     
}
int main()
{
    int i,j;
    while(scanf("%d%d%d",&k,&c,&m)!=-1)
    {
        vn = k+c+2;                  
        distnum = 0;
        src = 0;
        des = k+c+1;
        for(i=1;i<=k+c;++i)
        {
            for(j=1;j<=k+c;++j)
            {
                scanf("%d",&graph[i][j]);
                if(graph[i][j]==0) graph[i][j]=INF;   //输入的数据中0代表无穷大(此处注意变换)
            }
        }
        Floyd();                   //使用Floyd算法求出最短距离
        for(i=k+1;i<=k+c;++i)
        {
            for(j=1;j<=k;++j)
              dist[distnum++] = graph[i][j];
        }
        sort(dist,dist+distnum);       //对奶牛和奶牛机之间的距离排序
        int l=0,r=distnum-1,mid;
        while(l+1<r)            //枚举
        {
            mid = (l+r)/2;           
            length = dist[mid];
            if(build())  r = mid;
            else l = mid;   
        }
        if(distnum==1)       //注意考虑只有一个元素的情况
        {
            printf("%d\n",dist[0]);
        }
        else if(l+1==r)
        {
             length = dist[l];
             if(build())
             {
                 printf("%d\n",length);
             }  
             else
             {
                 length = dist[r];
                 if(build())
                    printf("%d\n",length);     
             }
        }      
        /*  也可采用这种方法进行枚举 （但是时间效率比较低,极易超时）
        int l=0,r=10000,mid;         
        while(l<r)
        {
            mid = (l+r)/2;           
            length = mid;
            if(build())  r = mid;   //此处不要写成mid+1，因为流量正好等于c 
            else l = mid+1;   
        }
        printf("%d\n",r);
        */
    }
    //getch();
    return 0;
}
