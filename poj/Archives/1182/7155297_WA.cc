#include<stdio.h>
#include<stdlib.h>
int father[50001],n,k,key[50001],ans;
int getfather(int x)
{
	if(father[x]==x) return x;
	key[x]=(key[x]+key[father[x]]+3)%3;
	return father[x]=getfather(father[x]);
}
void check(int a, int b, int type)
{
	int x=getfather(a), y=getfather(b);
	if(x==y)
	{
		if((key[y]-key[x]+3)%3!=type)
			++ans;
		return;
	}
	father[x]=y;
	key[x]=(key[y]-key[x]-type+6)%3;
}
int main()
{
	int d,x,y;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i) father[i]=i;
	for(int i=1;i<=k;++i)
	{
		scanf("%d%d%d",&d,&x,&y);
		if(x>n||y>n||d==2&&x==y)
			++ans;
		else
		{
			if(d==1) d=0;
			check(x,y,d);
		}
	}
	printf("%d\n",ans);
	return 0;
}
