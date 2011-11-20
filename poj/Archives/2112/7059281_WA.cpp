#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int v[300][300],map[300][300],f[300][300],s,t,oo=99999999;
int list[300],layer[300],que[300];
int path[300],judge,minf=oo;
bool found=false,vis[300];
int counter[300];
int n,k,c,m;
inline int max(int a, int b){return a>b?a:b;}
void init()
{
	memset(map,0,sizeof(map));
	n=k+c;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			scanf("%d",&map[i][j]);
			f[i][j]=map[i][j];
		}
}
void aug(int now)
{
	int i,tmp=minf,minl=t-1;
	if(now==t)
	{
		found=true;
		judge+=minf;
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
bool sap(int cut)
{
	
	s=1,t=n+2;
	memset(v,0,sizeof(v));
	memset(list,0,sizeof(list));
	memset(layer,0,sizeof(layer));
	memset(path,0,sizeof(path));
	memset(counter,0,sizeof(counter));
	for(int i=1;i<=k;++i)
		v[s][i+1]=m;
	for(int i=1;i<=k;++i)
		for(int j=k+1;j<=k+c;++j)
			if(f[i][j]<=cut)
				v[i+1][j+1]=1;
	for(int i=k+1;i<=k+c;++i) v[i+1][t]=1;
	judge=0;
	counter[0]=t+1;
	while(layer[s]<t)
	{
		minf=oo;
		found=false;
		aug(s);
	}
	return judge==c;
}
void work()
{
	int maxl=46001;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i) if(k!=i)
			for(int j=1;j<=n;++j) if(k!=j&&i!=j)
				if(f[i][k]&&f[k][j])
					if(!f[i][j]||f[i][k]+f[k][j]<f[i][j]) f[i][j]=f[i][k]+f[k][j];
	int left=0,right=maxl,ans,mid;
	while(left<right-1)
	{
		mid=left+right>>1;
		if(sap(mid)) right=mid;
		else left=mid;
	}
	while(sap(right))
	{
		ans=right;
		--right;
	}
	printf("%d\n",ans);
}
int main()
{
	while(scanf("%d%d%d",&k,&c,&m)!=EOF)
	{
		init();
		work();
	}
	return 0;
}
