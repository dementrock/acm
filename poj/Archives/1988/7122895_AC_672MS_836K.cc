#include<stdio.h>
#include<stdlib.h>
int father[30001],loc[30001],dis[30001],end[30001];
inline int max(int a, int b){return a>b?a:b;}
inline int abs(int x){return x>0?x:-x;}
int getfather(int x)
{
	if(father[x]==x)
		return x;
	int t=getfather(father[x]);
	loc[x]=loc[father[x]]+dis[x];
	father[x]=t;
	dis[x]=loc[x];
	return t;
}
int main()
{
	int t,i,j;
	char c;
	scanf("%d\n",&t);
	for(int i=1;i<=30000;++i) {father[i]=i;end[i]=i;}
	while(t--)
	{
		scanf("%c %d",&c,&i);
		if(c=='M')
		{
			scanf("%d\n",&j);	
			int x=getfather(i),y=getfather(j);
			if(x==y) continue;
			father[x]=y;
			getfather(end[y]);
			dis[x]=loc[end[y]]+1;
			end[y]=end[x];
		}
		else if(c=='C')
		{
			scanf("\n");	
			getfather(i);
			printf("%d\n",dis[i]);
		}
	}
}
