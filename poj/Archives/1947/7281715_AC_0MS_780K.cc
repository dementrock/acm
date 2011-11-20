#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[200][200],map[200][200],vis[200],son[200][200],oo=999999999;
int n,p;
inline int min(int a, int b){return a>b?b:a;}
void createtree(int x, int k)
{
	vis[x]=true;
	for(int i=1;i<=son[x][0];++i)
		if(!vis[son[x][i]]&&son[x][i]!=k)
			createtree(son[x][i],x);
	f[x][1]=son[x][0];
	for(int i=1;i<=son[x][0];++i)
		for(int j=p;j>=1;--j) if(f[x][j]!=oo)
			for(int k=p-j;k>=1;--k) if(f[son[x][i]][k]!=oo)
				f[x][j+k]=min(f[x][j+k],f[x][j]+f[son[x][i]][k]-2);
}
int main()
{
	int x,y,ans=oo;
	scanf("%d%d",&n,&p);
	for(int i=1;i<n;++i)
	{
		scanf("%d%d",&x,&y);
		map[x][y]=map[y][x]=1;
		son[x][++son[x][0]]=y,son[y][++son[y][0]]=x;
	}
	for(int i=0;i<200;++i) for(int j=0;j<200;++j) f[i][j]=oo;
	createtree(1,0);
	for(int i=1;i<=n;++i) if(f[i][p]<ans) ans=f[i][p];
	printf("%d\n",ans);
	return 0;
}
