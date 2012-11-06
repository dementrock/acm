#include<iostream>
#include<cstdio>
#include<string.h>
using namespace std;
const int maxn=20001;
const int maxm=200001;
struct node
{
	int x,y,f,op,next;
}g[maxm*5+maxn*2];
int F,first[maxn],now[maxn],sumd[maxn];
int dis[maxn],fanhui[maxn],pre[maxn],T,s,tot;
void add(int x,int y,int c)
{
     tot++;
     g[tot].x=x; g[tot].y=y; g[tot].f=c; g[tot].op=tot+1;
     g[tot].next=first[x]; first[x]=tot;
     tot++;
     g[tot].x=y; g[tot].y=x; g[tot].f=0; g[tot].op=tot-1;
     g[tot].next=first[y]; first[y]=tot;    
}
void maxflow()
{
	int i,flow,t,j,tmp,Min;
	bool flag;
	memset(dis,0,sizeof(dis));
	memset(sumd,0,sizeof(sumd));
	for(i=1;i<=T;i++)
		now[i]=first[i];
	sumd[0]=T; F=0;
	i=s; flow=999999999;
	while(dis[s]<T)
	{
		fanhui[i]=flow;
		flag=false;
		t=now[i];
		while(t!=0)
		{
			j=g[t].y;
			if((g[t].f>0)&&(dis[j]+1==dis[i]))
			{
				flag=true;
				pre[j]=t;
				now[i]=t;
				if(g[t].f<flow)
					flow=g[t].f;
				i=j;
				if(i==T)
				{
					F+=flow;
					while(i!=s)
					{
						g[pre[i]].f-=flow;
						g[g[pre[i]].op].f+=flow;
						i=g[pre[i]].x;
					}
					flow=999999999;
				}
				break;
			}
			t=g[t].next;
		}
		if(flag)
			continue;
		Min=T-1;
		t=first[i];
		while(t!=0)
		{
			if((g[t].f>0)&&(dis[g[t].y]<Min))
			{
				Min=dis[g[t].y];
				now[i]=t;
			}
			t=g[t].next;
		}
		sumd[dis[i]]--;
		if(sumd[dis[i]]==0) break;
		dis[i]=Min+1;
		sumd[dis[i]]++;
		if(i!=s)
		{
			i=g[pre[i]].x; 
			flow=fanhui[i];
		}
	}
}
int main()
{
	int N,M,i,x,y,c;
	scanf("%d %d",&N,&M);
	tot=0;s=N+1;T=N+2;
	memset(first,0,sizeof(first));
	for(i=1;i<=N;i++)
	{
		scanf("%d %d",&x,&y);
		add(s,i,x);
		add(i,T,y);
	}
	for(i=0;i<M;i++)
	{
		scanf("%d %d %d",&x,&y,&c);
		add(x,y,c);
		add(y,x,c);
	}
	maxflow();
	printf("%d\n",F);
	return 0;
}
