#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void print(char str[]){
	int i;
	for(i=0;i<strlen(str);){
		if(i+2<strlen(str)&&str[i]=='y'&&str[i+1]=='o'&&str[i+2]=='u'){
			printf("we");
			i+=3;
		}else{
			printf("%c",str[i]);
			++i;
		}
	}
	printf("\n");
}
int main(){
	while(1){
		int eof=1,len=0;
		char str[1001]={},c;
		while(scanf("%c",&c)!=EOF){
			eof=0;
			if(c=='\n') break;
			str[len++]=c;
		}
		if(eof) break;
		print(str);
	}
	return 0;
} 
