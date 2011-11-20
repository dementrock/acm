#include<stdio.h>
#include<string.h>
long long f[201][201];
void dp(int i, int j){
	if(i==j||j==1){
		f[i][j]=1;
		return;
	}
	if(i<j){
		f[i][j]=0;
		return;
	}
	if(f[i-j][j-1]==-1) dp(i-j,j-1);
	if(f[i-1][j-1]==-1) dp(i-1,j-1);
	f[i][j]=f[i-j][j-1]+f[i-1][j-1];
}
int main(){
	int n,k;
	memset(f,0xff,sizeof(f));
	while(scanf("%d%d",&n,&k)){
		if(!n&&!k) break;
		if(f[n][k]==-1)
			dp(n,k);
		printf("%I64d\n",f[n][k]);
	}
}
