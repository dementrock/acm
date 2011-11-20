#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int stick[100],used[100],n,tot,now,total;
inline int min(int a, int b){
	return a<b?a:b;
}
int dfs(int deep, int left, int former){
	if(!left){
		if(deep>=total) return 1;
		return dfs(deep+1,now,1);
	}
	if(former>n) return 0;
	if(stick[former]==stick[former-1]&&!used[former-1]||stick[former]>left||used[former])
		return dfs(deep,left,former+1);
	int t;
	used[former]=1;
	t=dfs(deep,left-stick[former],former+1);
	used[former]=0;
	if(t) return 1;
	if(left==now) return 0;
	t=dfs(deep,left,former+1);
	return t;
}
int check(int tnow, int ttotal){
	now=tnow,total=ttotal;
	return dfs(1,now,1);
}
inline int max(int a, int b){
	return a>b?a:b;
}
int cmp(const void *a, const void *b){
	return *(int*)b-*(int*)a;
}
int main(){
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		int sum=0,start=0;
		memset(used,0,sizeof(used));
		for(int i=1;i<=n;++i){
			scanf("%d",&stick[i]);
			sum+=stick[i];
			start=max(start,stick[i]);
		}
		qsort(stick+1,n,sizeof(stick[0]),cmp);
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
