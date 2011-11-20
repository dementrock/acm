#include<stdio.h>
#include<stdlib.h>
int n,k,w,t,appear[101][1001],judge[101],ansc,ans;
char c;
int main()
{
	scanf("%d %d\n",&n,&k);
	for(int i=1;i<=k;++i)
	{
		scanf("%d",&w);
		for(int j=1;j<=w;++j) 
		{
			scanf(" %d",&t);
			appear[i][t]=1;
		}
		for(int j=1;j<=w;++j) 
		{
			scanf(" %d",&t);
			appear[i][t]=2;
		}
		scanf("\n%c\n",&c);
		if(c=='<') judge[i]=-1;
		else if(c=='=') judge[i]=0;
		else if(c=='>') judge[i]=1;
	}
	for(int x=1;x<=n;++x)
	{
		bool flagg=false;
		for(int y=-1;y<=1;y+=2)
		{
			bool flag=true;
			for(int i=1;i<=k;++i)
			{
				if(!appear[i][x])
				{
					if(judge[i])
					{
						flag=false;
						break;
					}
					else continue;
				}
				else
				{
					if(judge[i]==0)
					{
						flag=false;
						break;
					}
					if(appear[i][x]==1)
					{
						if(judge[i]==y) continue;
						else
						{
							flag=false;
							break;
						}
					}
					else
					{
						if(judge[i]!=y) continue;
						else
						{
							flag=false;
							break;
						}
					}
				}
			}
			if(flag) flagg=1;
		}
		if(flagg){++ansc;ans=x;}
	}
	if(ansc==1) printf("%d\n",ans);
	else printf("0\n");
}
