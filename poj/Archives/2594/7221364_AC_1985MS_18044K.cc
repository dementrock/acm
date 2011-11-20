#include<stdio.h>
#include<string.h>
#define MAXN 1501
int vis[MAXN],Link[MAXN],v[MAXN][MAXN],f[MAXN][MAXN],n,m,ans;
int can(int now){
	for(int i=1;i<=2*n;++i){
		if(!vis[i]&&v[now][i]){
			vis[i]=1;
			if(!Link[i]||can(Link[i])){
				Link[i]=now;
				return i;
			}
		}
	}
	return 0;
}
int main(){
	int a,b;
	while(scanf("%d %d\n",&n,&m)!=EOF){
		if(!n&&!m) break;
		memset(f,0,sizeof(f));
		memset(v,0,sizeof(v));
		memset(Link,0,sizeof(Link));
		for(int i=1;i<=m;++i){
			scanf("%d %d\n",&a,&b);
			f[a][b]=1;
		}
		for(int k=1;k<=n;++k)
			for(int i=1;i<=n;++i) if(i!=k)
				for(int j=1;j<=n;++j) if(i!=j&&k!=j)
					f[i][j]|=f[i][k]&f[k][j];
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(f[i][j])
					v[i][j+n]=1;
		ans=0;
		for(int i=1;i<=n;++i){
			memset(vis,0,sizeof(vis));
			if(can(i)){
				++ans;
			}
		}
		printf("%d\n",n-ans);
	}
	return 0;
}
