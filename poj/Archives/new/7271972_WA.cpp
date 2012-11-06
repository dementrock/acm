#include<stdio.h>
#include<string.h>
#define oo 0x77777777
int vis[2001][2001],f[2001][2001],n,L,C,sum[2001];
inline int min(int a, int b){
	return a<b?a:b;
}
int cost(int j, int i){
	if(j>i) 
		return 0;
	int t=sum[i]-sum[j-1];
	t=L-t;
	if(t<=0) return 0;
	else if(1<=t&&t<=10)
		return -C;
	else
		return (t-10)*(t-10);
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
		f[i][j]=min(f[i][j],f[i-1][k-1]+cost(k,j));
	}
}
int main(){
	int counter=0,n,x;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		++counter;
		scanf("%d%d",&L,&C);
		memset(f,0x77,sizeof(f));
		memset(sum,0,sizeof(sum));
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;++i){
			scanf("%d",&x);
			sum[i]=sum[i-1]+x;
		}
		for(int i=1;;++i){
			if(!vis[i][n])
				dp(i,n);
			if(f[i][n]<oo){
				printf("Case %d:\n\n",counter);
				printf("Minimum number of lectures: %d\n",i);
				printf("Total dissatisfaction index: %d\n\n",f[i][n]);
				break;
			}
		}
	}
	return 0;
}
