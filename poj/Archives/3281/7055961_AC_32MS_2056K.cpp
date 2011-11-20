#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int v[800][800],s,t,oo=99999999;
int list[800],layer[800];
int path[800],ans,minf=oo;
bool found=false;
int counter[800];
int n,f,d;
void aug(int now)
{
	int i,tmp=minf,minl=t-1;
	if(now==t)
	{
		found=true;
		ans+=minf;
		return;
	}
	for(i=s;i<=t;++i)
	{
		if(v[now][i]>0)
		{
			if(layer[now]==layer[i]+1)
			{
				if(v[now][i]<minf) minf=v[now][i];
				aug(i);
				if(layer[s]>=t) return;
				if(found) break;
				minf=tmp;
			}
			if(layer[i]<minl) minl=layer[i];
		}
	}
	if(!found)
	{
		--counter[layer[now]];
		if(counter[layer[now]]==0) layer[s]=t;
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
	while(layer[s]<t)
	{
		minf=oo;
		found=false;
		aug(s);
	}
}
int main()
{
	int tf,td,x;
	scanf("%d%d%d",&n,&f,&d);
	s=0;
	t=2*n+2*f+2*d+1;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&tf,&td);
		for(int j=1;j<=tf;++j)
		{
			scanf("%d",&x);
			v[x+f][2*f+i]=1;
		}
		for(int j=1;j<=td;++j)
		{
			scanf("%d",&x);
			v[2*f+i+n][x+2*f+2*n]=1;
		}
	}
	for(int i=1;i<=f;++i) v[s][i]=v[i][i+f]=1;
	for(int i=1;i<=d;++i) v[2*f+2*n+i][2*f+2*n+d+i]=v[2*f+2*n+d+i][t]=1;
	for(int i=1;i<=n;++i) v[2*f+i][2*f+n+i]=1;
//	for(int i=s;i<=t;++i)
//		for(int j=s;j<=t;++j) if(v[i][j]) printf("%d %d %d\n",i,j,v[i][j]);
	counter[0]=t+1;
	sap();
	printf("%d\n",ans);
	return 0;
}
