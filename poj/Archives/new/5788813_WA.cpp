/*
pku1014
Dividing
动态规划
2009-8-31
*/
#include<iostream>
#include<stdio.h>
using namespace std;
int a[10]={},num=0;
bool judge()
{
	int counter=0, use[10]={};
	int sum=0;
	bool f[10][100]={false};
	for(int i=1;i<=6;i++)
		if(a[i])
		{
			use[counter++]=i;
			sum+=i;
		}
	if(sum%2!=0)
		return false;
	sum/=2;
	f[0][use[0]]=true;
	for(int i=1;i<counter;i++)
		for(int j=0;j<=sum;j++)
		{
			f[i][j]=f[i][j]|f[i-1][j];
			if(j-a[i]>=0)
				f[i][j]=f[i][j]|f[i-1][j-use[i]];
		}
	return f[counter-1][sum];
}
int main()
{
	int sum=0;
	while(1)
	{
		num++;
		sum=0;
		for(int i=1;i<=6;i++)
		{
			a[i]=0;
			scanf("%d",&a[i]);
			sum+=a[i];
			a[i]%=2;
		}
		if(sum==0)
			break;
		printf("Collection #%d:\n", num);
		if(judge())
			printf("Can be divided.\n");
		else
			printf("Can't be divided.\n");
	}
	return 0;
}
