#include<stdio.h>
#include<string.h>
int f[101][101],num[101][101],vis[101][101],n;
inline int max(int a, int b){
	return a>b?a:b;
}
void dp(int x, int y){
	vis[x][y]=1;
	f[x][y]=num[x][y];
	if(x-1>=1){
		if(!vis[x-1][y]) dp(x-1,y);
		f[x][y]=max(f[x][y],f[x-1][y]+num[x][y]);
	}
	if(y-1>=1){
		if(!vis[x][y-1]) dp(x,y-1);
		f[x][y]=max(f[x][y],f[x][y-1]+num[x][y]);
	}
}
int main(){
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		int x,y;
		memset(f,0,sizeof(f));
		memset(num,0,sizeof(num));
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;++i){
			scanf("%d %d",&x,&y);
			++num[x][y];
		}
		dp(100,100);
		printf("%d\n",f[100][100]);
	}
	printf("*\n");
	return 0;
}
