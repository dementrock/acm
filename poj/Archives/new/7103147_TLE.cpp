#include<stdio.h>
#include<string.h>
short f[5001][5001],n;
char s[5001],ts[5001];
inline short max(short x, short y){return x>y?x:y;}
void dp(int x, int y)
{
	f[x][y]=0;
	if(!x||!y) return;
	if(f[x][y-1]==-1) dp(x,y-1);
	if(f[x-1][y]==-1) dp(x-1,y);
	f[x][y]=max(f[x][y-1],f[x-1][y]);
	if(s[x-1]==ts[y-1])
	{
		if(f[x-1][y-1]==-1) dp(x-1,y-1);
		f[x][y]=max(f[x][y],f[x-1][y-1]+1);
	}
}
int main()
{
	scanf("%d\n",&n);
	scanf("%s\n",s);
	for(int i=0;i<n;++i) ts[i]+=s[n-1-i];
	memset(f,0xff,sizeof(f));
	f[0][0]=0;
	dp(n,n);
	printf("%d\n",n-f[n][n]);
	return 0;
}
