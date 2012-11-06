#include<iostream>
#include<string>
using namespace std;
string s[201];
int a[201],n,m;
int get(string s)
{
	int res=0;
	for(int i=0;i<s.length();++i)
		for(int j=i+1;j<s.length();++j)
			if(s[i]>s[j]) ++res;
	return res;
}
void swap(int &a, int &b){int x=a;a=b;b=x;}
void swap(string &a, string &b){string x=a;a=b;b=x;}
void quicksort(int left, int right)
{
	if(left>=right) return;
	int i=left+right>>1,j;
	swap(a[i],a[right]);
	swap(s[i],s[right]);
	for(i=left-1,j=left;j<right;++j)
		if(a[j]<a[right]||a[j]==a[right]&&s[j]<s[right])
		{
			swap(a[++i],a[j]);
			swap(s[i],s[j]);
		}
	swap(a[++i],a[right]);
	swap(s[i],s[right]);
	quicksort(left,i-1);
	quicksort(i+1,right);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;++i)
	{
		cin>>s[i];
		a[i]=get(s[i]);
	}
	quicksort(1,m);
	for(int i=1;i<=m;++i)
		cout<<s[i]<<endl;
	return 0;
}
