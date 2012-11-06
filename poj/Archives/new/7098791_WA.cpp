#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char s[100]={};
int n,ans,Comb[101][101];
int comb(int i, int j)
{
	if(i<0||j<0) return 1;
	if(Comb[i][j])
		return Comb[i][j];
	if(!i||!j||i==j)
		return Comb[i][j]=1;
	return Comb[i][j]=comb(i-1,j)+comb(i-1,j-1);
}
void work()
{
	for(int i=1;i<n;++i)
		ans+=comb(26,i);
	int used[101]={},pre=-1;
	for(int i=0;i<n;++i)
	{
		int sum=0;
		for(int j=pre+1;j<s[i]-'a';++j)
		{
			if(!used[j])
				ans+=comb(26-j-1,n-i-1);
		}
		pre=s[i]-'a';
		used[s[i]-'a']=1;
	}
	++ans;
}
int main()
{
	while(scanf("%s\n",s)!=EOF)
	{
		ans=0;
		n=strlen(s);
		work();
		printf("%d\n",ans);
	}
	return 0;
}
