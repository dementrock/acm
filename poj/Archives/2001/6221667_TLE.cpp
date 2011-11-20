#include<string.h>
#include<stdio.h>
#include<stdlib.h>
int n=0;
char str[1001][21];
bool cmp(char a[], int b, char c[]){
	for(int i=0;i<b;++i) if(a[i]!=c[i]) return false;
	return true;
}
int main()
{
	while(scanf("%s",str[++n]));
	for(int i=1;i<=n;++i){
		bool flagger=false;
		for(int j=1;j<=strlen(str[i]);++j){
			bool flag=true;
			for(int k=1;k<=n;++k) if(i!=k)
				if(cmp(str[i],j,str[k])){
					flag=false;
					break;
				}
			if(flag){
				for(int k=0;k<j;++k) printf("%c",str[i][k]);
				printf("\n");
				flagger=true;
				break;
			}
		}
		if(!flagger) printf("%s\n",str[i]);
	}
	return 0;
}
