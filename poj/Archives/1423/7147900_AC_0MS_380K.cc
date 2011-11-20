#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
double pi=3.1415926535,e=2.718281828;
int main(){
	int n,k;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&k);
		printf("%d\n",int((0.5*log(2*pi*k)+k*log(k/e))/log(10))+1);
	}
	return 0;
}
