#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int c[1000002],prime[100000],pnum,ans[100000];
int judge(int x){
	return x%4==1;
}
void getans(){
	for(int i=5;i<=1000001;i+=4)
		if(!c[i]){
			prime[++pnum]=i;
			for(int j=i+i;j<=1000001;j+=i)
				c[j]=1;
		}
	memset(c,0,sizeof(c));
	for(int i=1;i<pnum;++i){
		if(prime[i]*prime[i]>1000001) break;
		for(int j=i;prime[i]*prime[j]<=1000001&&j<=pnum;++j)
			c[prime[i]*prime[j]]=1;
	}
	for(int i=2;i<=1000001;++i) c[i]+=c[i-1];
}
int main(){
	int n;
	getans();
	while(scanf("%d",&n)){
		if(!n) break;
		printf("%d %d\n",n,c[n]);
	}
	return 0;
}
