#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int v[110][110],s,t,oo=99999999;
int list[110],layer[110];
int path[110],ans,minf=oo;
bool found=false;
int counter[110];
int n,np,nc,m;
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
void init()
{
	char str[1000];
	s=0,t=n+2;
	ans=0;
	memset(v,0,sizeof(v));
	memset(list,0,sizeof(list));
	memset(layer,0,sizeof(layer));
	memset(path,0,sizeof(path));
	memset(counter,0,sizeof(counter));
	for(int i=1;i<=m;++i)
	{
		scanf("%s",str);
		int pos=1,a=0,b=0;
		while(str[pos]!=',')
			a=a*10+str[pos++]-'0';
		++pos;
		while(str[pos]!=')')
			b=b*10+str[pos++]-'0';
		++a;
		++b;
		for(++pos;pos<strlen(str);++pos) v[a][b]=v[a][b]*10+str[pos]-'0';
	}
	for(int i=1;i<=np;++i)
	{
		scanf("%s",str);
		int pos=1,a=0;
		while(str[pos]!=')')
			a=a*10+str[pos++]-'0';
		++a;
		for(++pos;pos<strlen(str);++pos) v[s][a]=v[s][a]*10+str[pos]-'0';
	}
	for(int i=1;i<=nc;++i)
	{
		scanf("%s",str);
		int pos=1,a=0;
		while(str[pos]!=')')
			a=a*10+str[pos++]-'0';
		++a;
		for(++pos;pos<strlen(str);++pos) v[a][t]=v[a][t]*10+str[pos]-'0';
	}
}
int main()
{
	while(scanf("%d%d%d%d",&n,&np,&nc,&m)!=EOF)
	{
		init();
		counter[0]=t+1;
		sap();
		printf("%d\n",ans);
	}
	return 0;
}
