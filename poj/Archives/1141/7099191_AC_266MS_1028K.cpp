#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;
string s,ans[101][101],maxstring;
int f[101][101],vis[101][101],oo=999999999;
int min(int a, int b){return a>b?b:a;}
void dp(int i, int j)
{
	vis[i][j]=1;
	f[i][j]=oo;
	if(i==j)
	{
		if(s[i]=='('||s[i]==')')
		{
			f[i][j]=2;
			ans[i][j]="()";
		}
		else if(s[i]=='['||s[i]==']')
		{
			f[i][j]=2;
			ans[i][j]="[]";
		}
		return;
	}
	int type=-1;
	if(s[i]=='('&&s[j]==')'||s[i]=='['&&s[j]==']')
	{
		if(i==j-1)
		{
			f[i][j]=2;
			ans[i][j]+=s[i];
			ans[i][j]+=s[j];
		//	cout<<ans[i][j]<<endl;
			return;
		}
		if(!vis[i+1][j-1]) dp(i+1,j-1);
		f[i][j]=2+f[i+1][j-1];
		ans[i][j]+=s[i];
		ans[i][j]+=ans[i+1][j-1];
		ans[i][j]+=s[j];
	}
//		cout<<i<<" "<<j<<" "<<ans[i+1][j]<<" "<<ans[i][j]<<endl;
//		cout<<i<<" "<<j<<" "<<ans[i][j]<<endl;
	for(int k=i;k<j;++k)
	{
		if(!vis[i][k]) dp(i,k);
		if(!vis[k+1][j]) dp(k+1,j);
		if(f[i][k]+f[k+1][j]<f[i][j])
		{
			f[i][j]=f[i][k]+f[k+1][j];
			type=k;
		}
	}
	if(type>=0)
		ans[i][j]=ans[i][type]+ans[type+1][j];
}
int main()
{
	cin>>s;
	if(!s.length())
	{
		printf("\n");
		return 0;
	}
	for(int i=1;i<=1000;++i) maxstring+="lzsb";
	dp(0,s.length()-1);
	cout<<ans[0][s.length()-1]<<endl;
}
