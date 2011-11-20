#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void work()
{
	
	int list[80000],vis[80000],step[80000],closed=-1,open=0,t,tmp[5][5],now[5][5],tnow;
	char c=0;
	for(int i=1;i<=4;++i)
	{
		for(int j=1;j<=4;++j)
		{
			scanf("%c",&c);
			list[0]=(list[0]<<1)+(c=='w'?0:1);
		}
		scanf("\n");
	}
	if(list[0]==0||list[0]==(1<<16)-1)
	{
		printf("0\n");
		return;
	}
	vis[list[0]]=true;
	step[0]=0;
	while(closed<open)
	{
		++closed;
		tnow=list[closed];
		for(int i=16;i>=1;--i)
		{
			now[((i-1)>>2)+1][((i-1)&3)+1]=tnow&1;
			tnow>>=1;
		}
		for(int i=1;i<=4;++i)
			for(int j=1;j<=4;++j)
			{
				t=0;
				memcpy(tmp,now,sizeof(now));
				tmp[i][j]=1-tmp[i][j];
				if(i-1>=1) tmp[i-1][j]=1-tmp[i-1][j];
				if(j-1>=1) tmp[i][j-1]=1-tmp[i][j-1];
				if(i+1<=4) tmp[i+1][j]=1-tmp[i+1][j];
				if(j+1<=4) tmp[i][j+1]=1-tmp[i][j+1];
				for(int xi=1;xi<=4;++xi)
					for(int xj=1;xj<=4;++xj) t=(t<<1)+tmp[xi][xj];
				if(!vis[t])
				{
					vis[t]=true;
					list[++open]=t;
					step[open]=step[closed]+1;
				}
				if(!t||t==(1<<16)-1)
				{
					printf("%d\n",step[closed]+1);
					return;
				}
			}
	}
	printf("Impossible\n");
}
int main()
{
	work();
	return 0;
}
