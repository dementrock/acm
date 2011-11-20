#include<stdio.h>
#include<string.h>
struct Stick{
	int s, n;
} stick[100];
int tstick[100],n,tot;
int dfs(int deep, int left, int now, int maxdeep){
	if(!left){
		if(deep>=maxdeep) return 1;
		return dfs(deep+1,now,now,maxdeep);
	}
	for(int i=tot;i>=1;--i) if(stick[i].n&&stick[i].s<=left){
		--stick[i].n;
		int t=dfs(deep,left-stick[i].s,now,maxdeep);
		++stick[i].n;
		if(t) return 1;
	}
	return 0;
}
int check(int now, int total){
	return dfs(1,now,now,total);
}
inline int max(int a, int b){
	return a>b?a:b;
}
int main(){
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		memset(tstick,0,sizeof(tstick));
		tot=0;
		int sum=0,x,start=0;
		for(int i=1;i<=n;++i){
			scanf("%d",&x);
			++tstick[x];
			sum+=x;
			start=max(start,x);
		}
		for(int i=1;i<=50;++i) if(tstick[i]){++tot,stick[tot].s=i,stick[tot].n=tstick[i];}
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
