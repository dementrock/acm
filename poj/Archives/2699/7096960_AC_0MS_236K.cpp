#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
using namespace std;
int n,score[11],v[101][101],
V[101][101],layer[101],
oo=999999999,sum,s,t,
minf,ans,found,
counter[101],
maxflow;
void swap(int &a, int &b){int x=a;a=b;b=x;}
inline int min(int a, int b){return a>b?b:a;}
inline int max(int a, int b){return a<b?b:a;}
int turn(int a, int b)
{
	int i=min(a,b),j=max(a,b);
	return n+(2*n-i)*(i-1)/2+j-i;
}
void init()
{
	char c;
	n=0;
	sum=0;
	memset(score,0,sizeof(score));
	string s;
	while(scanf("%c",&c)!=EOF)
	{
		if(c=='\n') break;
		s+=c;
	}
	int t=0;
	while(t<s.length())
	{
		int now=0;
		for(int i=t;i<s.length()&&'0'<=s[i]&&s[i]<='9';++i,t=i)
			now=now*10+s[i]-'0';
		score[++n]=now;
		sum+=now;
		while((s[t]<'0'||s[t]>'9')&&t<s.length()) ++t;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<n;++j)
			if(score[j]<score[j+1])
				swap(score[j],score[j+1]);
	memset(V,0,sizeof(V));
}
void createmap()
{
	s=0,t=n*(n+1)/2+1;
	for(int i=1;i<=n;++i) V[s][i]=score[i];
	for(int i=n+1;i<=n*(n+1)/2;++i) V[i][t]=1;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(i!=j)
				V[i][turn(i,j)]=1;
}
void cutedge(int now)
{
	for(int i=1;i<now;++i)
		if(score[i]>score[now])
			V[i][turn(i,now)]=0;
}
void aug(int now)
{
	int i,tmp=minf,minl=t-1;
	if(now==t)
	{
		maxflow+=minf;
		found=true;
		return;
	}
	for(i=s;i<=t;++i)
		if(v[now][i]>0)
		{
			if(layer[now]==layer[i]+1)
			{
				minf=min(minf,v[now][i]);
				aug(i);
				if(layer[s]>=t) return;
				if(found) break;
				minf=tmp;
			}
			minl=min(minl,layer[i]);
		}
	if(!found)
	{
		--counter[layer[now]];
		if(!counter[layer[now]]) layer[s]=t;
		layer[now]=minl+1;
		++counter[layer[now]];
	}
	else
	{
		v[now][i]-=minf;
		v[i][now]+=minf;
	}
}
void sap()
{
	counter[0]=t+1;
	memset(layer,0,sizeof(layer));
	memcpy(v,V,sizeof(V));
	maxflow=0;
	while(layer[s]<t)
	{
		found=false;
		minf=oo;
		aug(s);
	}
}
void work()
{
	for(int i=2;i<=n;++i)
	{
		cutedge(i);
		sap();
		if(maxflow!=sum)
		{
			printf("%d\n",i-1);
			return;
		}
	}
	printf("%d\n",n);
}
int main()
{
	int m;
	scanf("%d\n",&m);
	while(m--)
	{
		init();
		createmap();
		work();
	}
	return 0;
}
