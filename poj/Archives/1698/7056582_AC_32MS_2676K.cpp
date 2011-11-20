#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int v[800][800],s,t,oo=99999999;
int list[800],layer[800],day[21][8],d[21],w[21];
int path[800],ans,minf=oo;
bool found=false;
int counter[800];
int n;
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
	memset(list,0,sizeof(list));
	memset(layer,0,sizeof(layer));
	memset(path,0,sizeof(path));
	memset(counter,0,sizeof(counter));
	counter[0]=t+1;
	ans=0;
	while(layer[s]<t)
	{
		minf=oo;
		found=false;
		aug(s);
	}
}
int main()
{
	int ttt,maxw=0;
	scanf("%d",&ttt);
	for(int times=1;times<=ttt;++times)
	{
		int tans=0;
		memset(day,0,sizeof(day));
		memset(d,0,sizeof(d));
		memset(w,0,sizeof(w));
		memset(v,0,sizeof(v));
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=7;++j) scanf("%d",&day[i][j]);
			scanf("%d%d",&d[i],&w[i]);
			tans+=d[i];
			maxw=maxw<w[i]?w[i]:maxw;
		}
		s=0,t=n+maxw*7+1;
		for(int i=1;i<=n;++i)
		{
			v[s][i]=d[i];
			for(int j=1;j<=w[i];++j)
				for(int k=1;k<=7;++k)
					if(day[i][k])
					{
						v[i][(j-1)*7+n+k]=oo;
						v[(j-1)*7+n+k][t]=1;
					}
		}
		sap();
		printf("%s\n",ans==tans?"Yes":"No");
	}
	return 0;
}
