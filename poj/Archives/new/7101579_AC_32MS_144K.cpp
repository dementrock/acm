#include<stdio.h>
#include<iostream>
using namespace std;
int f[100];
void solve(int now)
{
	int n=now*2;
	for(int delta=now+1;;delta+=(delta%(now+1)?now:1))
	{
	//	cout<<delta<<endl;
		int counter=0,vis[100]={},flag=1,num=0;
		for(int i=(delta-1)%n;;i=(i+delta-1)%(n-num))
		{
	//		cout<<i<<endl;
			if(num<now&&i<now)
			{
		//		cout<<delta<<" "<<num<<" "<<i<<" "<<now<<endl;
			//	system("pause");
				flag=0;
				break;
			}
			++num;
			
			if(num==n) break;
		}
		if(flag)
		{
			f[now]=delta;
			return;
		}
	}
}
int main()
{
	for(int i=1;i<=13;++i) solve(i);
	while(1)
	{
		int t;
		scanf("%d",&t);
		if(!t) break;
		printf("%d\n",f[t]);
	}
	return 0;
}
