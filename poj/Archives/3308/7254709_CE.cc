#include <iostream>
#include "float.h"
#include "math.h"
using namespace std;
#define MinN(x,y) ((x)<(y)?(x):(y))
#define Zero(x) (fabs(x)<EPS)
const int maxn=105;
const double INF=DBL_MAX;
const double EPS=1e-10;
double map[maxn][maxn];
double flow[maxn][maxn];
int pre[maxn];
double min_flow[maxn];
int stack[maxn];
bool visited[maxn];
bool Next_Path(int point_num,int source,int sink)//DFS
{
	memset(pre,-1,sizeof(pre));
	memset(visited,0,sizeof(visited));
	int top=-1;
	stack[++top]=source;
	visited[source]=true;
	min_flow[source]=INF;
	while(top>=0)
	{
		int temp=stack[top--];
		for(int i=0;i<point_num;i++)
		{
			if(!visited[i]&&!Zero(map[temp][i]-flow[temp][i]))
			{
				min_flow[i]=MinN(min_flow[temp],map[temp][i]-flow[temp][i]);
				pre[i]=temp;
				if(i==sink) return true;
				stack[++top]=i;
				visited[i]=true;
			}
		}
	}
	return false;
}
double Max_Flow(int point_num,int source,int sink)
{
	double max_flow=0;
	memset(flow,0,sizeof(flow));
	while(Next_Path(point_num,source,sink))
	{
		int t=sink;
		while(pre[t]>=0)
		{
			flow[pre[t]][t]+=min_flow[sink];
			flow[t][pre[t]]-=min_flow[sink];
			t=pre[t];
		}
		max_flow+=min_flow[sink];
	}
	return max_flow;
}
int main()
{
		int T,row,column,n;
		double cost;
		scanf("%d",&T);
		while(T--)
		{
			memset(map,0,sizeof(map));
			scanf("%d%d%d",&row,&column,&n);
			for(int i=0;i<row;i++)
			{
				scanf("%lf",&cost);
				map[row+column][i]=log(cost);
			}
			for(int i=0;i<column;i++)
			{
				scanf("%lf",&cost);
				map[i+row][row+column+1]=log(cost);
			}	
			for(int i=0;i<n;i++)
			{
				int a,b;
				scanf("%d%d",&a,&b);
				map[a-1][row+b-1]=INF;
			}
			double ans=Max_Flow(row+column+2,row+column,row+column+1);
			printf("%.4lf\n",exp(ans));
		}
	return 0;
}
