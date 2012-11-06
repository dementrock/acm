#include<stdio.h>
#include<string.h>
int stick[100],n;
int check(int now, int tot){
	int past[100],size=n;
	memcpy(past,stick,sizeof(stick));
	while(size){
		int f[100]={},pre[100]={};
		f[0]=1;
		for(int i=1;i<=50;++i) {
			for(int k=1;k<=past[i];++k){
				for(int j=now;j>=i;--j){
					if(f[j-i]){
						f[j]=1;
						pre[j]=i;
					}
				}
			}
		}
		if(!f[now]) return 0;
		int p=now;
		while(p&&pre[p]){
			--past[pre[p]];
			--size;
			p-=pre[p];
		}
	}
	return 1;
}
inline int max(int a, int b){
	return a>b?a:b;
}
int main(){
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		memset(stick,0,sizeof(stick));
		int sum=0,x,start=0;
		for(int i=1;i<=n;++i){
			scanf("%d",&x);
			++stick[x];
			sum+=x;
			start=max(start,x);
		} 
		for(int i=start;i<=sum;++i){
			if(!(sum%i)){
				if(check(i,sum/i)){
					printf("%d\n",i);
					break;
				}
			}
		}
	}
		return 0;
}
