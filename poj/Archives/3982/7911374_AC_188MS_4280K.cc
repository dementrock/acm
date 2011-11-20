#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int a[100][10001];
inline int max(int a, int b){return a>b?a:b;}
void print(int a[]){
	int i;
	printf("%d",a[a[0]]);
	for(i=a[0]-1;i>=1;--i){
		if(a[i]<10000) printf("0");
		if(a[i]<1000) printf("0");
		if(a[i]<100) printf("0");
		if(a[i]<10) printf("0");
		printf("%d",a[i]);
	}
	printf("\n");
}
void add(int a[], int b[]){
	int i;
	a[0]=max(a[0],b[0]);
	for(i=1;i<=a[0];++i){
		a[i]+=b[i];
		a[i+1]+=a[i]/100000;
		a[i]%=100000;
	}
	while(a[a[0]+1]){ a[a[0]+1]+=a[a[0]]/100000; a[a[0]++]%=100000;}
}
int main(){
	int i;
	a[0][0]=a[1][0]=a[2][0]=1;
	while(scanf("%d %d %d\n",&a[0][1],&a[1][1],&a[2][1])!=EOF){
		for(i=3;i<=99;++i){
			add(a[i],a[i-1]);
			add(a[i],a[i-2]);
			add(a[i],a[i-3]);
		}
		print(a[99]);
		memset(a,0,sizeof(a));
		a[0][0]=a[1][0]=a[2][0]=1;
	}
	return 0;
}
