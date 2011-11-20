#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int mon[20],lastmon,n,times;
double inv[20],earn;
double calc(double now){
	double ans=0;
	for(int i=1;i<=n;++i)
		ans+=inv[i]*pow(now,mon[i]);
	return ans;
}
int main(){
	while(scanf("%d",&n)){
		if(n==-1) break;
		++times;
		for(int i=1;i<=n;++i){
			scanf("%d%lf",&mon[i],&inv[i]);
		}
		scanf("%d%lf",&lastmon,&earn);
		for(int i=1;i<=n;++i) mon[i]=lastmon-mon[i]+1;
		double l=1.0,r=2.0;
		while(r-l>0.00001){
			double m=0.5*(l+r);
			if(calc(m)>earn)
				r=m;
			else
				l=m;
		}
		printf("Case %d: %.5lf\n\n",times,l-1);
	}
	return 0;
}
