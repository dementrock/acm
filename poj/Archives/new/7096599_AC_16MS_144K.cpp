#include<stdio.h>
int n,time[60],now[60],first[60],begin,last,ans=99999,tans;
inline int min(int a, int b){return a>b?b:a;}
int isok(int first, int d)
{
	for(int i=first;i<60;i+=d)
		if(time[i]-now[i]<=0) 
			return 0;
	return 1;
}
void mark(int first, int d, int plus)
{
	for(int i=first;i<60;i+=d)
		now[i]+=plus;
}
void dfs(int x)
{
	if(x==60)
	{
		ans=min(ans,tans);
		return;
	}
	if(tans>ans) return;
	if(time[x]-now[x]<=0)
	{
		int i;
		for(i=x+1;i<60;++i)
			if(time[i]-now[i]>0)
				break;
		dfs(i);
		return;
	}
	for(int i=begin;(i<<1)<x;++i)
		if(first[i])
			if(isok(x,x-i))
			{
				--first[i];
				mark(x,x-i,1);
				dfs(x);
				mark(x,x-i,-1);
				++first[i];
			}
	if((x<<1)<last)
	{
		++first[x];
		++now[x];
		++tans;
		dfs(x);
		--tans;
		--now[x];
		--first[x];
	}
}
void init()
{
	int t;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&t);
		if(i==1) begin=t;
		if(i==n) last=t;
		++time[t];
	}
}
int main()
{
	init();
	dfs(begin);
	printf("%d\n",ans);
	return 0;
}
