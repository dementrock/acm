#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
double dis[1001],mid,x[1001],y[1001],z[1001],l,r,oo=999999999;
int vis[1001],n,m;
void init()
{
	scanf("%d",&n);
	if(!n) exit(0);
	for(int i=1;i<=n;++i) scanf("%lf%lf%lf",&x[i],&y[i],&z[i]);
}
inline double calc(int a, int b)
{
	return abs(z[a]-z[b])-mid*sqrt((double)(x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}
double prim()
{
	double minspan=0,mindis=oo;
	int minj;
	memset(vis,0,sizeof(vis));
	vis[1]=true;
	dis[1]=0;
	for(int i=2;i<=n;++i) dis[i]=calc(1,i);
	for(int i=1;i<n;++i)
	{
		mindis=oo,minj=0;
		for(int j=2;j<=n;++j) if(!vis[j])
			if(dis[j]<mindis)
			{
				mindis=dis[j];
				minj=j;
			}
		vis[minj]=true;
		minspan+=mindis;
		for(int j=1;j<=n;++j)
		{
			double t=calc(minj,j);
			if(t<dis[j]) dis[j]=t;
		}
	}
	return minspan;
//	printf("%.2f\n",minspan);
}
void work()
{
	l=0,r=10000000;
	while(r-l>0.0001)
	{
		mid=0.5*(l+r);
		if(prim()<0)
			r=mid;
		else l=mid;
	//	printf("%.3lf %.3lf\n",l,r);
	}
	printf("%.3lf\n",l);
}
int main()
{
	while(1)
	{
		init();
		work();
	}
	return 0;
}
