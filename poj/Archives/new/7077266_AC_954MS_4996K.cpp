#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int sg[10001],s[101],k,can[10001]={};
void find(int x)
{
	int t[10001]={};
	for(int i=1;i<=k;++i)
	{
		if(x-s[i]>=0)
		{
			if(sg[x-s[i]]==-1)
				find(x-s[i]);
			t[sg[x-s[i]]]=1;
		}
	}
	for(int i=0;i<=10000;++i) if(!t[i])
	{
		sg[x]=i;
	//	printf("%d %d\n",x,sg[x]);
		return;
	}
}
int main()
{
	while(1)
	{
		memset(sg,0xff,sizeof(sg));
		sg[0]=0;
		int m;
		scanf("%d",&k);
		if(!k) break;
		for(int i=1;i<=k;++i)
		{
			scanf("%d",&s[i]);
			can[s[i]]=1;
		}
		scanf("%d",&m);
		for(int i=1;i<=m;++i)
		{
			int x=0,h,l;
			bool flag=false;
			scanf("%d",&l);
			for(int j=1;j<=l;++j)
			{
				scanf("%d",&h);
				if(sg[h]==-1) find(h);
				x^=sg[h];
				//printf("%d %d\n",x,sg[h]);
			}
			if(x) printf("W");
			else printf("L");
		}
		printf("\n");
	}
}
