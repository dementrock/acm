#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

#define INF 99999999
#define min( a, b ) ( (a)< (b)?(a): (b) )

struct point
{

    double x;
    double y;
}p[200];

int pre[200];//记录该节点的前驱
double graph[200][200], ans;//图数组和结果
bool   visit[110], circle[110];//visit记录该点有没有被访问过，circle记录改点是不是在一个圈里
int    n, m, root;//顶点数+边数+根节点标号

void dfs( int t )//一个深度优先搜索，搜索出一个最大的联通空间
{
    int i;
    visit[t]= true;
    for(i= 1; i<= n; ++i )
    {
        if( !visit[i] && graph[t][i]!= INF )
            dfs( i );
    }
}

bool check()//这个函数用来检查最小树形图是否存在，即如果存在，那么一遍dfs后，应该可以遍历到所有的节点
{
    memset( visit, false, sizeof(visit) );
    dfs( root );
    
    for( int i= 1; i<= n; ++i )
    {
        if( !visit[i] ) 
            return false;
    }
    return true;
}

double dist( int i, int j )
{
    return sqrt( (p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y) );
}

int exist_circle()//判断图中是不是存在有向圈
{
    int i;
    int j;
    root= 1; pre[root]= root;
    for(i= 1; i<= n; ++i )
    {
        if( !circle[i] && i!= root )
        {
            pre[i]= i; graph[i][i]= INF;
            
            for(j= 1; j<= n; ++j )
            {
                if( !circle[j] && graph[j][i]< graph[pre[i]][i] )
                    pre[i]= j;
            }
        }
    }//这个for循环负责找出所有非根节点的前驱节点
    for( i= 1; i<= n; ++i )
    {
        if( circle[i] ) 
            continue;
        memset( visit, false, sizeof(visit) );
        int j= i;
        while( !visit[j] ) 
        { 
            visit[j]= true; 
            j= pre[j]; 
        }
        if( j== root )
            continue;
        
        return j;
    }//找圈过程，最后返回值是圈中的一个点
    
    return -1;//如果没有圈，返回-1
}


void  update( int t )//缩圈之后更新数据
{
    int i;
    int j;
    ans+= graph[pre[t]][t];
    for(i=pre[t]; i!= t; i= pre[i] )
    {
        ans+= graph[pre[i]][i];
        circle[i]= true;
    }//首先把圈里的边权全部加起来，并且留出t节点，作为外部接口
    
    for(i= 1; i<= n; ++i )
        if( !circle[i] && graph[i][t]!= INF )
            graph[i][t]-= graph[pre[t]][t];
    //上面这个for循环的作用是对t节点做更新操作，为什么要单独做？你可以看看线面这个循环的跳出条件。
    for(j= pre[t]; j!= t; j= pre[j] )
        for( int i= 1; i<= n; ++i )
        {
            if( circle[i] ) 
                continue;
            if( graph[i][j]!= INF )
            graph[i][t]= min( graph[i][t], graph[i][j]- graph[pre[j]][j] );
            /**///////////////////////////////////////////////////////////////////////////
            graph[t][i]= min( graph[j][i], graph[t][i] );
        }
    //这个循环对圈中的其他顶点进行更新
}

void solve()
{
    int j;
    memset( circle, false, sizeof(circle) );
    while( ( j= exist_circle() )!= -1 ) 
        update( j );
    
    for( j= 1; j<= n; ++j )
        if( j!= root && !circle[j] )
            ans+= graph[pre[j]][j];
    
    printf("%.2f\n", ans );
}

int main()
{
    int i;
    while( scanf("%d%d",&n,&m)!= EOF )
    {
        for(i= 0; i<= n; ++i )
            for( int j= 0; j<= n; ++j )
                graph[i][j]= INF;
        
        for(i= 1; i<= n; ++i )
            scanf("%lf%lf",&p[i].x, &p[i].y );
        
        for(i= 0; i< m; ++i )
        {
            int a, b;
            scanf("%d%d",&a,&b);
            graph[a][b]= dist( a, b );
        }
        
        root= 1; 
        ans= 0;
        if( !check() ) 
            printf("poor snoopy\n");
        else  
            solve();
    }
    
    return 0;
}
