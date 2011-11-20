#include<stdio.h>
#include<string.h>
bool v[201][201]={false},used[201]={false};
int linked[201]={};
int N,M;
void init()
{
	int i,j,a,b;
	for(i=1;i<=N;i++)
	{
		scanf("%d",&a);
		for(j=1;j<=a;j++)
		{
			scanf("%d",&b);
			v[i][b]=true;
		}
	}
}
int can(int t)
{
	int i;
	for(i=1;i<=M;i++)
	{
		if(!used[i]&&v[t][i])
		{
			used[i]=true;
			if(linked[i]==0||can(linked[i]))
			{
				linked[i]=t;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	while(scanf("%d%d",&N,&M)!=EOF){
		memset(linked,0,sizeof(linked));
		memset(v,0,sizeof(v));
		init();
		int ans=0,i;
		for(i=1;i<=N;i++)
		{
			memset(used,false,sizeof(used));
			if(can(i))
				ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
