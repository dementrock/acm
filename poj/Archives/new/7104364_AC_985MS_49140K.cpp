#include<stdio.h>
#include<string.h>
short f[5001][5001],n;
char s[5001],ts[5001];
inline short max(short x, short y){return x>y?x:y;}
int main()
{
	scanf("%d\n",&n);
	scanf("%s\n",s);
	for(int i=0;i<n;++i) ts[i]=s[n-1-i];
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			f[i][j]=max(f[i-1][j],f[i][j-1]);
			if(s[i-1]==ts[j-1]) f[i][j]=max(f[i][j],f[i-1][j-1]+1);
		}
	printf("%d\n",n-f[n][n]);
	return 0;
}
