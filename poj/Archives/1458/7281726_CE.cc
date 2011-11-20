#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
string s1,s2;
int f[1001][1001];
inline int max(int a, int b){return a>b?a:b;}
void dp(int x, int y)
{
	f[x][y]=0;
	if(!x||!y) return;
	if(s1[x-1]==s2[y-1])
	{
		if(f[x-1][y-1]==-1) dp(x-1,y-1);
		f[x][y]=max(f[x][y],f[x-1][y-1]+1);
	}
	if(f[x][y-1]==-1) dp(x,y-1);
	f[x][y]=max(f[x][y],f[x][y-1]);
	if(f[x-1][y]==-1) dp(x-1,y);
	f[x][y]=max(f[x][y],f[x-1][y]);
}
int main()
{
	while(cin>>s1>>s2)
	{
		memset(f,0xff,sizeof(f));
		f[0][0]=0;
		dp(s1.length(),s2.length());
		cout<<f[s1.length()][s2.length()]<<endl;
	}
	return 0;
}
