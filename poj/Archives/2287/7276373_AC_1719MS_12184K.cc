#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1001
int tian[MAXN],king[MAXN],vis[MAXN][MAXN],f[MAXN][MAXN],g[MAXN][MAXN],n,ans,oo=0x77777777;
int cmp(const void *a, const void *b){
	return *(int*)b-*(int*)a;
}
inline int max(int a, int b){
	return a>b?a:b;
}
void dp(int x, int y){
	vis[x][y]=1;
	f[x][y]=-oo;
	if(!x||y>x) return;
	if(x>y){
		if(!vis[x-1][y]) dp(x-1,y);
		if(f[x-1][y]>-oo)
			f[x][y]=max(f[x][y],f[x-1][y]+g[n-(x-y)+1][x]);
	}
	if(y){
		if(!vis[x-1][y-1]) dp(x-1,y-1);
		if(f[x-1][y-1]>-oo)
			f[x][y]=max(f[x][y],f[x-1][y-1]+g[y][x]);
	}
}
int main(){
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		for(int i=1;i<=n;++i) scanf("%d",&tian[i]);
		for(int i=1;i<=n;++i) scanf("%d",&king[i]);
		qsort(tian+1,n,sizeof(tian[0]),cmp);
		qsort(king+1,n,sizeof(king[0]),cmp);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(tian[i]<king[j])
					g[i][j]=-200;
				else if(tian[i]==king[j])
					g[i][j]=0;
				else g[i][j]=200;
			}
		}
		memset(vis,0,sizeof(vis));
		f[0][0]=0,vis[0][0]=1;
		ans=-oo;
		for(int i=0;i<=n;++i){
			if(!vis[n][i]){
				dp(n,i);
			}
			ans=max(ans,f[n][i]);
		}
		printf("%d\n",ans);
	}
}
