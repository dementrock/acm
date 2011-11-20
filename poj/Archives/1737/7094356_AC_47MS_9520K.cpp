#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 10000
int n,g[51][MAXN],f[51][MAXN],comb[51][51][MAXN],vis[51][51],tmp[MAXN];
inline int max(int a, int b){return a>b?a:b;}
void print(int f[])
{
	int len=f[0];
	printf("%d",f[len]);
	for(int i=len-1;i>=1;--i)
	{
		if(f[i]<1000) printf("0");
		if(f[i]<100) printf("0");
		if(f[i]<10) printf("0");
		printf("%d",f[i]);
	}
	printf("\n");
}
void handel(int a[])
{
	for(int i=1;i<=a[0];++i)
	{
		a[i+1]+=a[i]/10000;
		a[i]%=10000;
	}
	while(a[a[0]+1])
	{
		++a[0];
		a[a[0]+1]+=a[a[0]]/10000;
		a[a[0]]%=10000;
	}
}
void multc(int a[], int k)
{
	for(int i=1;i<=a[0];++i) a[i]*=k;
	handel(a);
}
void add(int a[], int b[])
{
	for(int i=1;i<=b[0];++i)
		a[i]+=b[i];
	handel(a);
}
void mult(int a[], int b[])
{
	int c[MAXN]={};
	for(int i=1;i<=a[0];++i)
		for(int j=1;j<=b[0];++j)
			c[i+j-1]+=a[i]*b[j];
	c[0]=a[0]+b[0]-1;
	handel(c);
	memcpy(a,c,sizeof(c));
}
void subtract(int a[], int b[])
{
	for(int i=a[0];i>=1;--i)
	{
		--a[i+1];
		a[i]=a[i]+10000-b[i];
		a[i+1]+=a[i]/10000;
		a[i]%=10000;
	}
}
void findcomb(int i, int j)
{
	vis[i][j]=true;
	if(i==1||j==0||i==j)
	{
		comb[i][j][0]=comb[i][j][1]=1;
		return;
	}
	if(!vis[i-1][j]) findcomb(i-1,j);
	if(!vis[i-1][j-1]) findcomb(i-1,j-1);
	comb[i][j][0]=1;
	add(comb[i][j],comb[i-1][j]);
	add(comb[i][j],comb[i-1][j-1]);
}
void work()
{
	g[0][0]=g[0][1]=2;
	for(int i=1;i<=50;++i)
	{
		g[i][0]=g[i][1]=1;
		for(int j=1;j<=(i-1)*i/2;++j)
			multc(g[i],2);
	}
	f[1][0]=f[1][1]=1;
	f[2][0]=f[2][1]=1;
	for(int i=0;i<=50;++i)
		for(int j=0;j<=i;++j)
			if(!vis[i][j])
				findcomb(i,j);
	for(int i=3;i<=50;++i)
	{
		memcpy(f[i],g[i],sizeof(g[i]));
		for(int j=1;j<=i-1;++j)
		{
			memset(tmp,0,sizeof(tmp));
			tmp[0]=tmp[1]=1;
			mult(tmp,comb[i-1][j-1]);
			mult(tmp,f[j]);
			mult(tmp,g[i-j]);
			
		subtract(f[i],tmp);
		}
	}
}
int main()
{
	work();
	while(1)
	{
		scanf("%d",&n);
		if(!n) return 0;
		print(f[n]);
	}
	return 0;
}
