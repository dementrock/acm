#include<stdio.h>
#include<string.h>
int stick[100],n;
int check(int now, int tot){
	int past[100],size=n;
	memcpy(past,stick,sizeof(stick));
	//printf("%d %d\n",now,tot);
	while(size){
		int f[4000]={},pre[4000]={};
		f[0]=1;
		//	printf("%d\n",size);
		for(int i=50;i>=1;--i) {
		//	printf("%d\n",i);
			for(int k=1;k<=past[i];++k){
				for(int j=now;j>=i;--j){
					if(f[j-i]&&!f[j]){
						f[j]=1;
						pre[j]=i;
					}
				}
			}
		}
		if(!f[now]) return 0;
		int p=now,s=0;
	//	printf("%d\n",p);
		while(p){
			--past[pre[p]];
		//	printf("%d\n",pre[p]);
			--size;
			s+=pre[p];
			p-=pre[p];
		}
	//	printf("ok %d %d\n",p,s);
	//	for(int i=1;i<=50;++i)  if(past[i])printf("%d %d\n",i,past[i]);
	//		printf("-----------------------------\n");
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
