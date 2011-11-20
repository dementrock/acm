#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int cinx[101],ciny[101],v[101][101],nowv[101][101],tv[101][101],
nleft,vis[101],n,m,ans,pre[101],next[101],oo=999999999,list[101],
edgein[101][101],edgeout[101][101];
inline int dis(int x1, int y1, int x2, int y2)
{
	return int((double)sqrt((x1-x2)*(x1-x2)*1.0+(y1-y2)*(y1-y2)*1.0)*1000);
}
inline int min(int a, int b)
{
	return a>b?b:a;
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
	int others=0;
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
		for(int i=2;i<=n;++i)
		{
			int mink=oo,minj=0;
			for(int j=1;j<=n;++j) //求最小入边 
				if(nowv[j][i])	
					if(mink>nowv[j][i])
					{
						mink=nowv[j][i];
						minj=j;
					}
			pre[i]=minj;			//保存前驱后继 
			next[minj]=i;
			ans+=mink;
		//	printf("minedge:  %d %d %d\n",minj,i,mink);
		}
		int flag=0;
		for(int i=1;i<=n;++i)
		{
			if(!vis[i])
			{
				memset(list,0,sizeof(list));
				list[++list[0]]=i;
				vis[i]=i;
				int t=i,flagg=0;
				while(next[t])		//	寻找环 
				{
					vis[next[t]]=i;
					if(next[t]==i)
					{
						flagg=1;
						break;
					}
					list[++list[0]]=next[t];
					t=next[t];
				}
				flag|=flagg;
				if(flagg)			//若有环，将i作为收缩后点的编号 
				{
					others+=nowv[list[list[0]]][i];
					for(int j=1;j<list[0];++j) others+=nowv[list[j]][list[j+1]];
					memcpy(tv,nowv,sizeof(nowv));
					for(int j=1;j<=list[0];++j)			//先消除所有包含环内点的边 
						for(int k=1;k<=n;++k)
							tv[list[j]][k]=tv[k][list[j]]=0;
					for(int j=1;j<=list[0];++j)
					{
						int now=list[j],in=nowv[pre[list[j]]][list[j]];
						for(int k=1;k<=n;++k)
						{
							if(vis[k]!=i)
							{
								if(nowv[now][k])	//若为出边 
									tv[i][k]=nowv[now][k];
								else if(nowv[k][now])  //若为入边
									tv[k][i]=nowv[k][now]-in; 
							} 
						}
					}
				}
			}
		}
		if(!flag)	//若无环
		{
			printf("%.2f\n",1.0*(ans+others)*0.001);
			return;
		}
		else memcpy(nowv,tv,sizeof(tv));
	}
}
int main()
{
//	freopen("3164.in","r",stdin);
//	freopen("3164.out","w",stdout);
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		init();
		for(int i=1;i<=n;++i)
			if(scanf("%d%d",&cinx[i],&ciny[i])==EOF) return 0;
		int i,j;
		for(int k=1;k<=m;++k)
		{
			if(scanf("%d%d",&i,&j)==EOF) return 0;
			if(i==j||j==1) continue;
			edgein[j][++edgein[j][0]]=i;
			edgeout[i][++edgeout[i][0]]=j;
			v[i][j]=dis(cinx[i],ciny[i],cinx[j],ciny[j]);
		}
		work();
	}
	return 0;
}
