#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
double cinx[101],ciny[101],v[101][101],nowv[101][101],tv[101][101],ans;
int nleft,vis[101],n,m,pre[101],next[101],oo=999999999,list[101],tlist[101],cut[101],appear[101],deal[101];
inline double dis(int x1, int y1, int x2, int y2)
{
	return double((double)sqrt((x1-x2)*(x1-x2)*1.0+(y1-y2)*(y1-y2)));
}
void dfs(int now)
{
	--nleft;
	vis[now]=true;
	for(int i=1;i<=n;++i)
		if(v[now][i]&&!vis[i])
			dfs(i);
}
void init()
{
	memset(cinx,0,sizeof(cinx));
	memset(ciny,0,sizeof(ciny));
	memset(v,0,sizeof(v));
	memset(vis,0,sizeof(vis));
	ans=0;
}
void work()
{
	double others=0;
	nleft=n;
	dfs(1);			
	if(nleft)				//检查是否存在最小树形图 
	{
		printf("poor snoopy\n");
		return;
	}
	memcpy(nowv,v,sizeof(v));
	while(1)
	{
		ans=0;
		memset(pre,0,sizeof(pre));
		memset(tv,0,sizeof(tv));
		memset(vis,0,sizeof(vis));
		memset(next,0,sizeof(next));
		memset(deal,0,sizeof(deal));
		for(int i=2;i<=n;++i) if(!cut[i])
		{
			double mink=oo;
			int minj=0;
			for(int j=1;j<=n;++j) if(!cut[j])//求最小入边 
				if(nowv[j][i])	
					if(mink>nowv[j][i])
					{
						mink=nowv[j][i];
						minj=j;
					}
			pre[i]=minj;			//保存前驱后继 
			next[minj]=i;
			ans+=mink;
		}
		
		int flag=0;
		for(int i=1;i<=n;++i) if(!cut[i])
		{
			if(!vis[i]&&!deal[i])
			{
				memset(list,0,sizeof(list));
				memset(tlist,0,sizeof(tlist));
				memset(appear,0,sizeof(appear));
				tlist[++tlist[0]]=i;
				vis[i]=i;
				int t=i,flagg=0;
				while(pre[t])		//	寻找环 
				{
					if(deal[pre[t]]) break;
					if(vis[pre[t]]==i)
					{
						flagg=1;
						break;
					}
					vis[pre[t]]=i;
					tlist[++tlist[0]]=pre[t];
					t=pre[t];
				}
				flag|=flagg;
				if(flagg)			//若有环，将i作为收缩后点的编号 
				{
					int tmptt;
					for(int j=1;j<=tlist[0];++j) if(tlist[j]==pre[t])
					{
						tmptt=j;
						break;
					}
					for(int k=tmptt;k<=tlist[0];++k){ list[++list[0]]=tlist[k];appear[tlist[k]]=1;deal[tlist[k]]=1;}
					others+=nowv[list[list[0]]][list[1]];
					for(int j=1;j<list[0];++j)
						others+=nowv[list[j]][list[j+1]];
					memcpy(tv,nowv,sizeof(nowv));
					for(int j=1;j<=list[0];++j)			//先消除所有包含环内点的边 
						for(int k=1;k<=n;++k) if(!cut[k])
							tv[list[j]][k]=tv[k][list[j]]=0;
					for(int j=1;j<=list[0];++j)
					{
						int now=list[j];
						double in=nowv[pre[list[j]]][list[j]];
						for(int k=1;k<=n;++k) if(!cut[k])
						{
							if(!appear[k])
							{
							//	printf("%d %d %d %.2f\n",now,k,list[1],in);
								if(nowv[now][k])	//若为出边 
									if(tv[list[1]][k]==0||tv[list[1]][k]>nowv[now][k])
										tv[list[1]][k]=nowv[now][k];
								if(nowv[k][now]) //若为入边
									if(tv[k][list[1]]==0||tv[k][list[1]]>nowv[now][k]-in)
										tv[k][list[1]]=nowv[k][now]-in;
							} 
						}
					}
					for(int j=2;j<=list[0];++j) cut[list[j]]=1;
				}
			}
		}
		if(!flag)	//若无环
		{
			printf("%.2f\n",ans+others);
			return;
		}
		else memcpy(nowv,tv,sizeof(tv));
	}
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		init();
		for(int i=1;i<=n;++i)
			scanf("%lf%lf",&cinx[i],&ciny[i]);
		int i,j;
		for(int k=1;k<=m;++k)
		{
			scanf("%d%d",&i,&j);
			if(i==j||j==1) continue;
			v[i][j]=dis(cinx[i],ciny[i],cinx[j],ciny[j]);
		}
		work();
	}
	return 0;
}
