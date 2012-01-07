#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <climits>
using namespace std;
#ifndef ONLINE_JUDGE
ifstream fin("test.in");
#else
#define fin cin
#endif
int v;
const int maxn = 100;
double graph[maxn][maxn];
double x[maxn];
double y[maxn];
double result;
double dist[maxn];
int set[maxn];
void mst()
{
        set[0]=1;
            /*
             *     for(int i=0;i<v;i++)
             *             dist[i]=INT_MAX;
             *                 for(int i=1;i<v;i++)
             *                     {
             *                             if(graph[i][0]<dist[i])
             *                                         dist[i]=graph[i][0];
             *                                             }
             *                                                 */
            for(int k=0;k<v-1;k++)
                    {
                                double tempmin = INT_MAX;
                                        int tempj=0;
                                                int tempi=0;
                                                        for(int i=0;i<v;i++)
                                                                    {
                                                                                    for(int j=0;j<v;j++)
                                                                                                    {
                                                                                                                        if(set[i]==1&&set[j]==0&&graph[i][j]<tempmin)
                                                                                                                                            {
                                                                                                                                                                    tempmin=graph[i][j];
                                                                                                                                                                                        tempi=i;
                                                                                                                                                                                                            tempj=j;
                                                                                                                                                                                                                            }
                                                                                                                                    }
                                                                                            }
                                                                result+=tempmin;
                                                                        set[tempj]=1;
                                                                        /*
                                                                         *         //更新所有点到源的最短路
                                                                         *                 for(int i=0;i<v;i++)
                                                                         *                             if(set[i]==0&&dist[i]>dist[tempj]+graph[i][tempj])
                                                                         *                                             dist[i]=dist[tempj]+graph[i][tempj];
                                                                         *                                             */
                                                                            }
}
int main()
{
        int ncase;
            fin>>ncase;
                while(ncase--)
                        {
                                    fin>>v;
                                            memset(x,0,sizeof(x));
                                                    memset(y,0,sizeof(y));
                                                            memset(graph,0,sizeof(graph));
                                                                    memset(dist,0,sizeof(dist));
                                                                            memset(set,0,sizeof(set));
                                                                                    result = 0;
                                                                                            for(int i=0;i<v;i++)
                                                                                                            fin>>x[i]>>y[i];
                                                                                                    for(int i=0;i<v;i++)
                                                                                                                {
                                                                                                                                for(int j=v-1;j>=0;j--)
                                                                                                                                                {
                                                                                                                                                                    if(i!=j)
                                                                                                                                                                                        {
                                                                                                                                                                                                                graph[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                                                                                                                                                                                                                                    graph[j][i]=graph[i][j];
                                                                                                                                                                                                                                                    }
                                                                                                                                                                                    else
                                                                                                                                                                                                        {
                                                                                                                                                                                                                                graph[i][j]=INT_MAX;
                                                                                                                                                                                                                                                    graph[j][i]=INT_MAX;
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                }
                                                                                                                                        }
                                                                                                            mst();
                                                                                                                    printf("%.2lf\n",result);
                                                                                                                            if(ncase!=0)
                                                                                                                                            cout<<endl;
                                                                                                                                }
                    return 0;
}
