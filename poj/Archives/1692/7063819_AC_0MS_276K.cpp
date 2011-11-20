#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
int a[110],b[110],ma[110][110],mb[110][110],f[110][110];
inline int max(int a, int b)
{
	return a>b?a:b; 
}
void dp(int i, int j)
{
	if(i<=1||j<=1)
	{
		f[i][j]=0;
		return;
	}
	if(f[i-1][j]==-1) dp(i-1,j);
	if(f[i][j-1]==-1) dp(i,j-1);
	f[i][j]=max(f[i-1][j],f[i][j-1]);
	if(ma[i][j]&&mb[i][j]&&a[i]!=b[j])
	{
		if(f[mb[i][j]-1][ma[i][j]-1]==-1)
			dp(mb[i][j]-1,ma[i][j]-1);
		f[i][j]=max(f[i][j],f[mb[i][j]-1][ma[i][j]-1]+2);
	}
}
int main()
{
	int m,n1,n2;
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d",&n1,&n2);
		memset(f,0xff,sizeof(f));
		memset(ma,0,sizeof(ma));
		memset(mb,0,sizeof(mb));
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int i=1;i<=n1;++i) scanf("%d",&a[i]);
		for(int i=1;i<=n2;++i) scanf("%d",&b[i]);
		for(int i=1;i<=n1;++i)
			for(int j=1;j<=n2;++j)
				if(a[i]==b[j]){ma[i][j+1]=j;mb[i+1][j]=i;}
				else{ma[i][j+1]=ma[i][j];mb[i+1][j]=mb[i][j];}
		dp(n1,n2);
		printf("%d\n",f[n1][n2]);
	}
}
