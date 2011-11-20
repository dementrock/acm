#include<stdio.h>
#include<stdlib.h>
int n,m,s,t,v[1200][1200],out[1200][1200],oo=99999999;
int list[1200],layer[1200],pre[1200],pig[1200];
int path[1200],ans,minf=oo;
bool found=false;
int counter[1200];
void aug(int now)
{
	int i,tmp=minf,minl=t-1;
	if(now==t)
	{
		found=true;
		ans+=minf;
		return;
	}
	for(i=0;i<=t;++i)
	{
		if(v[now][i]>0)
		{
			if(layer[now]==layer[i]+1)
			{
				if(v[now][i]<minf) minf=v[now][i];
				aug(i);
				if(layer[0]>=t) return;
				if(found) break;
				minf=tmp;
			}
			if(layer[i]<minl) minl=layer[i];
		}
	}
	if(!found)
	{
		--counter[layer[now]];
		if(counter[layer[now]]==0) layer[0]=t;
		layer[now]=minl+1;
		++counter[layer[now]];
	}
	else
	{
		v[now][i]-=minf;
		v[i][now]+=minf;
		if(now<i)out[now][i]+=minf;
		else out[i][now]-=minf;
	}
}
void sap()
{
	while(layer[0]<t)
	{
		minf=oo;
		found=false;
		aug(0);
	}
}
int main()
{
	int a,x;
	scanf("%d%d",&m,&n);
	s=0,t=n+1;
	for(int i=1;i<=m;++i)
		scanf("%d",&pig[i]);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a);
		for(int j=1;j<=a;++j)
		{
			scanf("%d",&x);
			if(!pre[x])
				v[s][i]+=pig[x];
			else v[pre[x]][i]=oo;
			pre[x]=i;
		}
		scanf("%d",&x);
		v[i][t]+=x;
	}
	counter[0]=t+1;
	sap();
	printf("%d\n",ans);
	return 0;
}
