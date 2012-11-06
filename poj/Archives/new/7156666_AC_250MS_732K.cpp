#include<stdio.h>
#include<stdlib.h>
int father[50001],n,k,key[50001],delt[50001],ans;
int getfather(int x)
{
	int t=father[x];
	if(father[x]==x) return x;
	father[x]=getfather(father[x]);
	key[x]=(delt[x]+key[t])%3;
//	printf("now:%d father:%d relat:%d get:%d\n",x,father[x],delt[x],key[x]);

	delt[x]=key[x];
//	printf("now:%d father:%d relat:%d \n",x,father[x],key[x]);
	return father[x];
}
void check(int a, int b, int type)
{
	int x=getfather(a), y=getfather(b);
	if(x==y)
	{
		if((key[a]-key[b]+3)%3!=type)
			++ans;
		return;
	}
	father[x]=b;
	delt[x]=(type-key[a]+3)%3;
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
	//	printf("%d %d %d\n",d,x,y);
			if(d==1) d=0;
			check(x,y,d);
		}
	}
	printf("%d\n",ans);
	return 0;
}
