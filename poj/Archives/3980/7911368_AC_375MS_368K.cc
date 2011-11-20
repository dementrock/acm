#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int mod(int n, int m){
	return n-n/m*m;
}
int main(){
	int a,b;
	while(scanf("%d %d\n",&a,&b)!=EOF){
		printf("%d\n",mod(a,b));
	}
	return 0;
} 
