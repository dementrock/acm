#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXN 1001
int n,vis[MAXN],f[MAXN][2],edge[MAXN][MAXN],x[MAXN],y[MAXN],c[MAXN];
inline int max(int a, int b){
	return a>b?a:b;
}
inline int abs(int x){
	return x>0?x:-x;
}
void dfs(int now){
	vis[now]=1;
	for(int i=1;i<=edge[now][0];++i)
		if(!vis[edge[now][i]]){
			dfs(edge[now][i]);
			f[now][0]=max(f[now][0],f[edge[now][i]][0]);
			f[now][0]=max(f[now][0],f[edge[now][i]][1]);
			f[now][1]=max(f[now][1],f[now][1]+f[edge[now][i]][1]);
		}
	f[now][1]+=c[now];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d%d",&x[i],&y[i],&c[i]);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(abs(x[i]-x[j])+abs(y[i]-y[j])==1){
				edge[i][++edge[i][0]]=j;
				edge[j][++edge[j][0]]=i;
			}
	dfs(1);
	printf("%d\n",max(f[1][0],f[1][1]));
	return 0;
}
