#include<stdio.h>
#include<string.h>
#define oo 0x77777777
#define MAXN 1010
int vis[MAXN][MAXN],f[MAXN][MAXN],n,L,C,sum[MAXN],Cost[MAXN][MAXN],viscost[MAXN][MAXN];
inline int min(int a, int b){
	return a<b?a:b;
}
int cost(int j, int i){
	if(viscost[j][i])
		return Cost[j][i];
	viscost[j][i]=1;
	if(j>i) 
		return Cost[j][i]=0;
	int t=sum[i]-sum[j-1];
	t=L-t;
	if(t<=0) return Cost[j][i]=0;
	else if(1<=t&&t<=10)
		return Cost[j][i]=-C;
	else
		return Cost[j][i]=(t-10)*(t-10);
}
void dp(int i, int j){
	vis[i][j]=1;
	if(i==1){
		if(sum[j]<=L) 
			f[i][j]=cost(1,j);
		return;
	}
	for(int k=j+1;k>=2;--k){
		if(sum[j]-sum[k-1]>L) break;
		if(!vis[i-1][k-1])  dp(i-1,k-1);
		if(f[i-1][k-1]<oo)
			f[i][j]=min(f[i][j],f[i-1][k-1]+cost(k,j));
	}
}
int main(){
	int counter=0,n,x;
	while(scanf("%d",&n)!=EOF){
		int c=1;
		if(!n) break;
		++counter;
		scanf("%d%d",&L,&C);
		for(int i=0;i<=n+1;++i) for(int j=0;j<=n+1;++j) f[i][j]=oo,vis[i][j]=Cost[i][j]=viscost[i][j]=0;
		for(int i=1,tmp=0;i<=n;++i){
			scanf("%d",&x);
			sum[i]=sum[i-1]+x;
			tmp+=x;
			if(tmp>L){tmp=x;++c;}
		}
		dp(c,n);
		printf("Case %d:\n\n",counter);
		printf("Minimum number of lectures: %d\n",c);
		printf("Total dissatisfaction index: %d\n\n",f[c][n]);
	}
	return 0;
}
