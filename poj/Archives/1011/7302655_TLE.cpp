#include<stdio.h>
#include<string.h>
struct Stick{
	int s, n;
} stick[100];
int tstick[100],n,tot,now,total;
inline int min(int a, int b){
	return a<b?a:b;
}
int dfs(int deep, int left, int former){
//	printf("%d %d %d\n",deep,left,former);
	if(!left){
		if(deep>=total) return 1;
		return dfs(deep+1,now,tot);
	}
	if(!former) return 0;
	for(int i=former;i>=1;--i) if(left==stick[i].s){
		--stick[i].n;
		int t=dfs(deep+1,now,tot);
		++stick[i].n;
		return t;
	}
	for(int i=former;i>=1;--i) if(stick[i].n&&stick[i].s<=left){
		for(int j=min(stick[i].n,left/stick[i].s);j>=1;--j){
			stick[i].n-=j;
			int t=dfs(deep,left-stick[i].s*j,i-1);
			stick[i].n+=j;
			if(t) return 1;
			if(i==former&&left==now) return 0;
			if(stick[i].s==left) return 0;
		}
	}
	return 0;
}
int check(int tnow, int ttotal){
	now=tnow,total=ttotal;
	return dfs(1,now,tot);
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
