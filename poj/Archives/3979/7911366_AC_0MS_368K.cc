#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int n1[2], n2[2], ans[2];
void dealwith(int n[]){
	int i;
	for(i=2;i<=9;++i){
		while(!(n[0]%i)&&!(n[1]%i)){
			n[0]/=i, n[1]/=i;
		}
	}
}
void add(int n1[], int n2[]){
	ans[0]=n1[0]*n2[1]+n2[0]*n1[1];
	ans[1]=n1[1]*n2[1];
	dealwith(ans);
}
void subtract(int n1[], int n2[]){
	ans[0]=n1[0]*n2[1]-n2[0]*n1[1];
	ans[1]=n1[1]*n2[1];
	dealwith(ans);
}
void print(int n[]){
	if(!n[0]) printf("0\n");
	else if(n[1]==1) printf("%d\n",n[0]);
	else printf("%d/%d\n", n[0], n[1]);
}
int main(){
	char str[20];
	while(scanf("%s\n",str)!=EOF){
		n1[0]=str[0]-'0', n1[1]=str[2]-'0', n2[0]=str[4]-'0', n2[1]=str[6]-'0';
		if(str[3]=='+'){
			add(n1,n2);
		}else{
			subtract(n1,n2);
		}
		print(ans);
	}
	return 0;
} 
