#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
string stack[1001],s1,s2;
int snum=1;
int main(){
	stack[0]="Ignored";
	stack[1]="http://www.acm.org/";
	while(cin>>s1){
		if(s1=="VISIT"){
			cin>>s2;
			stack[++snum]=s2;
			cout<<stack[snum]<<endl;
		}else if(s1=="BACK"){
			if(snum>1){
				--snum;
				cout<<stack[snum]<<endl;
			}else cout<<stack[0]<<endl;
		}else if(s1=="FORWARD"){
			if(stack[snum+1].length()){
				++snum;
				cout<<stack[snum]<<endl;
			}else cout<<stack[0]<<endl;
		}else break;
	}
}
