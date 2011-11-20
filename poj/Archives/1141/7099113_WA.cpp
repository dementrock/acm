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
		if(!f[i+1][j-1]) dp(i+1,j-1);
		f[i][j]=2+f[i+1][j-1];
		ans[i][j]+=s[i];
		ans[i][j]+=ans[i+1][j-1];
		ans[i][j]+=s[j];
	}
	else
	{
		int type=0;
		if(!f[i+1][j]) dp(i+1,j);
		if(!f[i][j-1]) dp(i,j-1);
		if(f[i+1][j]+2<f[i][j])
		{
			f[i][j]=f[i+1][j]+2;
			type=-1;
		}
		if(f[i][j-1]+2<f[i][j])
		{
			f[i][j]=f[i][j-1]+2;
			type=-2;
		}
//		cout<<i<<" "<<j<<" "<<ans[i+1][j]<<" "<<ans[i][j]<<endl;
		f[i][j]=min(f[i][j],f[i][j-1]+2);
//		cout<<i<<" "<<j<<" "<<ans[i][j]<<endl;
		for(int k=i;k<j;++k)
		{
			if(!f[i][k]) dp(i,k);
			if(!f[k+1][j]) dp(k+1,j);
			if(f[i][k]+f[k+1][j]<f[i][j])
			{
				f[i][j]=f[i][k]+f[k+1][j];
				type=k;
			}
		}
		if(type==-1)
		{
			ans[i][j]+=s[i];
			ans[i][j]+=ans[i+1][j];
			ans[i][j]+=s[i]=='('?')':']';
		}
		else if(type==-2)
		{
			ans[i][j]+=s[j]==')'?'(':'[';
			ans[i][j]+=ans[i][j-1];
			ans[i][j]+=s[j];
		}
		else ans[i][j]=ans[i][type]+ans[type+1][j];
	}
//	cout<<i<<" "<<j<<" "<<ans[i][j]<<endl;
}
int main()
{
	cin>>s;
	for(int i=1;i<=1000;++i) maxstring+="lzsb";
	dp(0,s.length()-1);
	cout<<ans[0][s.length()-1]<<endl;
}
