#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int n,k;
long long Comb[101][101];
long long comb(int i, int j)
{
	if(i<0||j<0) return 1;
	if(Comb[i][j])
		return Comb[i][j];
	if(!i||!j||i==j)
		return Comb[i][j]=1;
	return Comb[i][j]=comb(i-1,j)+comb(i-1,j-1);
}
int main()
{
	while(scanf("%d%d",&n,&k))
	{
		if(!n&&!k) break;
		printf("%d things taken %d at a time is %I64d exactly.\n",n,k,comb(n,k));
	}
	return 0;
}
