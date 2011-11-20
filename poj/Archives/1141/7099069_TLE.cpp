#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;
string s,ans[101][101],maxstring;
int f[101][101];
string min(string a, string b){return a.length()>b.length()?b:a;}
void dp(int i, int j)
{
	f[i][j]=1;
	ans[i][j]=maxstring;
	if(i==j)
	{
		if(s[i]=='('||s[i]==')')
			ans[i][j]="()";
		else if(s[i]=='['||s[i]==']')
			ans[i][j]="[]";
		return;
	}
	if(s[i]=='('&&s[j]==')'||s[i]=='['&&s[j]==']')
	{
		if(i==j-1)
		{
			ans[i][j]=s[i]+s[j];
//			cout<<ans[i][j]<<endl;
			return;
		}
		if(!f[i+1][j-1]) dp(i+1,j-1);
		ans[i][j]=s[i]+ans[i+1][j-1]+s[j];
	}
	else
	{
		if(!f[i+1][j]) dp(i+1,j);
		if(!f[i][j-1]) dp(i,j-1);
		string t1;
		t1+=s[i];
		t1+=ans[i+1][j];
		t1+=s[i]=='('?')':']';
		string t2;
		t2+=s[j]==')'?'(':'[';
		t2+=ans[i][j-1];
		t2+=s[j];
		ans[i][j]=min(ans[i][j],t1);
//		cout<<i<<" "<<j<<" "<<ans[i+1][j]<<" "<<ans[i][j]<<endl;
		ans[i][j]=min(ans[i][j],t2);
//		cout<<i<<" "<<j<<" "<<ans[i][j]<<endl;
		for(int k=i;k<j;++k)
		{
			if(!f[i][k]) dp(i,k);
			if(!f[k+1][j]) dp(k+1,j);
			ans[i][j]=min(ans[i][j],ans[i][k]+ans[k+1][j]);
		}
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
