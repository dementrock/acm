#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int f[9][9][9][9][15],sum[9][9][9][9],a[9][9],n,oo=999999999;
double ave;
inline int min(int a, int b){return a>b?b:a;}
void get(int x1,int y1,int x2,int y2)
{
	if(x1==x2&&y1==y2)
	{
		sum[x1][y1][x2][y2]=a[x1][y1];
		return;
	}
	if(x1==x2)
	{
		if(sum[x1][y1][x2][y2-1]==-1)
			get(x1,y1,x2,y2-1);
		sum[x1][y1][x2][y2]=sum[x1][y1][x2][y2-1]+a[x2][y2];
		return; 
	}
	if(y1==y2)
	{
		if(sum[x1][y1][x2-1][y2]==-1)
			get(x1,y1,x2-1,y2);
		sum[x1][y1][x2][y2]=sum[x1][y1][x2-1][y2]+a[x2][y2];
		return;
	}
	if(sum[x1][y1][x2][y2-1]==-1) get(x1,y1,x2,y2-1);
	if(sum[x1][y2][x2][y2]==-1)   get(x1,y2,x2,y2);
	sum[x1][y1][x2][y2]=sum[x1][y1][x2][y2-1]+sum[x1][y2][x2][y2];
	
}
void dp(int x1, int y1, int x2, int y2, int k)
{
	f[x1][y1][x2][y2][k]=oo;
	if(k>x2-x1+y2-y1) return;
	if(!k)
	{
		f[x1][y1][x2][y2][k]=sum[x1][y1][x2][y2];
		return;
	}
	if(x1<x2)
		for(int i=x1;i<x2;++i)
		{
			if(f[i+1][y1][x2][y2][k-1]==-1)
				dp(i+1,y1,x2,y2,k-1);
			f[x1][y1][x2][y2][k]=min(f[x1][y1][x2][y2][k],f[i+1][y1][x2][y2][k-1]+sum[x1][y1][i][y2]);
		}
	if(y1<y2)
		for(int i=y1;i<y2;++i)
		{
			if(f[x1][i+1][x2][y2][k-1]==-1)
				dp(x1,i+1,x2,y2,k-1);
			f[x1][y1][x2][y2][k]=min(f[x1][y1][x2][y2][k],f[x1][i+1][x2][y2][k-1]+sum[x1][y1][x2][i]);
		}
}
int main()
{
	scanf("%d\n",&n);
	for(int i=1;i<=8;++i)
		for(int j=1;j<=8;++j)
		{
			scanf("%d",&a[i][j]);
			ave+=a[i][j];
		}
	ave/=1.0*n;
	memset(sum,0xff,sizeof(sum));
	memset(f,0xff,sizeof(f));
	for(int x1=1;x1<=8;++x1)
		for(int y1=1;y1<=8;++y1)
			for(int x2=x1;x2<=8;++x2)
				for(int y2=y1;y2<=8;++y2)
					if(sum[x1][y1][x2][y2]==-1)
						get(x1,y1,x2,y2);
	for(int x1=1;x1<=8;++x1)
		for(int y1=1;y1<=8;++y1)
			for(int x2=x1;x2<=8;++x2)
				for(int y2=y1;y2<=8;++y2)
					sum[x1][y1][x2][y2]*=sum[x1][y1][x2][y2];
	dp(1,1,8,8,n-1);
	double tmp=f[1][1][8][8][n-1];
	printf("%.3lf\n",sqrt(tmp/n-ave*ave));
	return 0;
}
