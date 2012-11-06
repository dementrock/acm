/*
给出n*m(n≤150,m≤10)的棋盘，要在上面放置2*3的骨牌，有一些方格无法放置，求最多能放置多少个。
*/
/*
Sol	:SCR
Time:...
Spc :O(3^m)
*/
/*
   i  i-1
0: 1   1
1: 0   1
2: 0   0 
*/
#include<cstdio>
#include<cstring>
int n,m,k,t,x,y,p;
bool f1[152][12],f2[152][12];
unsigned char a[2][59050];

void dfs(int x,int s1,int s2,int n)
{
	if(x>m+1)return;
	if(x==m+1){a[p&1][s1]>?=a[1-p&1][s2]+n; return;}
	if(f1[p][x])dfs(x+3,s1*27,s2*27+13,n+1);
	if(f2[p][x])dfs(x+2,s1*9,s2*9+8,n+1);
	dfs(x+1,s1*3+2,s2*3+1,n);
	dfs(x+1,s1*3+1,s2*3,n);
	dfs(x+1,s1*3,s2*3,n);
}

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&n,&m,&k);
		memset(a[1],0,sizeof(a[0]));
		memset(f1,1,sizeof(f1));
		memset(f2,1,sizeof(f2));
		while(k--)
		{
			scanf("%d%d",&x,&y);
			for(int i=0;i<2;i++)
				for(int j=0;j<3;j++)
				{
					if(y-j>=0)f1[x+i][y-j]=0;
					if(y-i>=0)f2[x+j][y-i]=0;
				}
		}
		for(int i=0;i<12;i++)f2[2][i]=0;
		for(p=2;p<=n;p++)
		{
			memset(a[p&1],0,sizeof(a[0]));
			dfs(1,0,0,0);
		}
		printf("%d\n",a[n&1][0]);
	}
}
  		
