#include<stdio.h>
int a[10001],now=1;
int main()
{
	a[1]=1;
	for(int i=2;;++i){
		bool flag=true;
		for(int j=1;j<=i;++j){
			a[++now]=i;
			if(now>=10000){
				flag=false;
				break;
			}
		}
		if(!flag) break;
	}
	int n=0;
	for(int i=1;i<=10000;++i) a[i]+=a[i-1];
	while(1){
		scanf("%d",&n);
		if(!n) return 0;
		printf("%d %d\n",n,a[n]);
	}
}
