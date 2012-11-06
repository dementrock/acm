#include<iostream>
#include<string>
#include<string.h>
using namespace std;
string s1,s2;
int l1,l2,f[101][101],oo=999999999,vis[101][101],t,cmp[5][5]={5,-1,-2,-1,-3,
															  -1,5,-3,-2,-4,
															  -2,-3,5,-2,-2,
															  -1,-2,-2,5,-1,
															  -3,-4,-2,-1,0};
inline int max(int a, int b){return a>b?a:b;}
int s(char c)
{
	if(c=='A') return 0;
	if(c=='C') return 1;
	if(c=='G') return 2;
	if(c=='T') return 3;
	return 4;
}
void dp(int i, int j)
{
	vis[i][j]=true;
	f[i][j]=-oo;
	if(!i&&!j){f[i][j]=0;return;}
	if(!i)
	{
		if(!vis[i][j-1]) dp(i,j-1);
		f[i][j]=f[i][j-1]+cmp[4][s(s2[j])];
		return;
	}
	if(!j)
	{
		if(!vis[i-1][j]) dp(i-1,j);
		f[i][j]=f[i-1][j]+cmp[s(s1[i])][4];
		return;
	}
	if(!vis[i-1][j-1]) dp(i-1,j-1);
	f[i][j]=max(f[i][j],f[i-1][j-1]+cmp[s(s1[i])][s(s2[j])]);
	if(!vis[i][j-1]) dp(i,j-1);
	f[i][j]=max(f[i][j],f[i][j-1]+cmp[4][s(s2[j])]);
	if(!vis[i-1][j]) dp(i-1,j);
	f[i][j]=max(f[i][j],f[i-1][j]+cmp[s(s1[i])][4]);
}
int main()
{
	scanf("%d\n",&t);
	char tt;
	while(t--)
	{
		s1=s2=" ";
		memset(vis,0,sizeof(vis));
		memset(f,0,sizeof(f));
		scanf("%d ",&l1);
		for(int i=1;i<=l1;++i){ scanf("%c",&tt);s1+=tt;}
		scanf("\n");
		scanf("%d ",&l2);
		for(int i=1;i<=l2;++i){ scanf("%c",&tt);s2+=tt;}
		scanf("\n");
		dp(l1,l2);
		printf("%d\n",f[l1][l2]);
	}
	return 0;
}
