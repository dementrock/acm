#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[301][31],minc[301][301],x[301],v,p,oo=999999999;
inline int min(int a, int b){return a>b?b:a;}
void dp(int i, int j)
{
	if(i==j)
	{
		f[i][j]=0;
		return;
	}
	if(j==1)
	{
		f[i][j]=minc[1][i];
		return;
	}
	f[i][j]=oo;
	for(int k=1;i-k>=j-1;++k)
	{
		if(f[i-k][j-1]==-1) dp(i-k,j-1);
		f[i][j]=min(f[i][j],f[i-k][j-1]+minc[i-k+1][i]);
	}
}
int main()
{
	memset(f,0xff,sizeof(f));
	scanf("%d%d",&v,&p);
	for(int i=1;i<=v;++i) scanf("%d",&x[i]);
	for(int i=1;i<=v;++i)
		for(int j=i;j<=v;++j)
		{
			int mid=i+j>>1;
			for(int k=i;k<mid;++k) minc[i][j]+=x[mid]-x[k];
			for(int k=j;k>mid;--k) minc[i][j]+=x[k]-x[mid];
		}
//	for(int i=0;i<=v;++i) for(int j=0;j<=p;++j)
	if(f[v][p]==-1) dp(v,p);
	printf("%d\n",f[v][p]);
}
