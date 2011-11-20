#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
using namespace std;
char s1[3001],s2[3001];
int t[2][3001][3001],pre[3001];
string c1,c2;
void swap(string *a, string *b){string x=*a;*a=*b;*b=x;}
void quicksort(string a[], int left, int right){
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(&a[i],&a[right]);
	for(j=left,i=left-1;j<right;++j)
		if(a[j]<a[right]) swap(&a[++i],&a[j]);
	swap(&a[++i],&a[right]);
	quicksort(a,left,i-1);
	quicksort(a,i+1,right);
}
string create(int now, int id)
{
	if(!t[id][now][0])
		return "()";
	string c[2000];
	for(int i=1;i<=t[id][now][0];++i)
		c[i]=create(t[id][now][i],id);
	quicksort(c,1,t[id][now][0]);
	string ans="(";
	for(int i=1;i<=t[id][now][0];++i) ans+=c[i];
	ans+=")";
	return ans;
}
int check()
{
	int now=1,maxn=1;
	for(int i=0;i<strlen(s1);++i)
	{
		if(!(s1[i]-'0'))
		{
			t[0][now][++t[0][now][0]]=maxn+1;
			pre[maxn+1]=now;
			now=++maxn;
		}
		else
			now=pre[now];
	}
	memset(pre,0,sizeof(pre));
	now=maxn=1;
	for(int i=0;i<strlen(s2);++i)
	{
		if(!(s2[i]-'0'))
		{
			t[1][now][++t[1][now][0]]=maxn+1;
			pre[maxn+1]=now;
			now=++maxn;
		}
		else
			now=pre[now];
	}
//	cout<<create(1,0)<<endl<<create(1,1)<<endl;
	return create(1,0)==create(1,1);
}
int main()
{
	int tt;
	scanf("%d\n",&tt);
	while(tt--)
	{
		memset(t,0,sizeof(t));
		scanf("%s\n%s\n",s1,s2);
		if(check())
			printf("same\n");
		else printf("different\n");
	}
	return 0;
} 
