#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
using namespace std;
char s1[3001],s2[3001];
short t[1501][3001],pre[3001];
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
string create(int now)
{
	if(!t[now][0])
		return "()";
	string c[3001];
	for(int i=1;i<=t[now][0];++i)
		c[i]=create(t[now][i]);
	quicksort(c,1,t[now][0]);
	string ans="(";
	for(int i=1;i<=t[now][0];++i) ans+=c[i];
	ans+=")";
//	cout<<now<<" "<<ans<<endl;
	return ans;
}
int check()
{
	string c1,c2;
	int now=1,maxn=1;
	for(int i=0;i<strlen(s1);++i)
	{
		if(!(s1[i]-'0'))
		{
			t[now][++t[now][0]]=maxn+1;
			pre[maxn+1]=now;
			now=++maxn;
		}
		else
			now=pre[now];
	}
	c1=create(1);
	memset(pre,0,sizeof(pre));
	memset(t,0,sizeof(t));
	now=maxn=1;
	for(int i=0;i<strlen(s2);++i)
	{
		if(!(s2[i]-'0'))
		{
			t[now][++t[now][0]]=maxn+1;
			pre[maxn+1]=now;
			now=++maxn;
		}
		else
			now=pre[now];
	}
	c2=create(1);
//	cout<<c1<<endl<<c2<<endl;
	return c1==c2;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int tt;
	scanf("%d\n",&tt);
	while(tt--)
	{
		memset(t,0,sizeof(t));
		memset(pre,0,sizeof(pre));
		scanf("%s\n%s\n",s1,s2);
		if(check())
			printf("same\n");
		else printf("different\n");
	}
	return 0;
} 
