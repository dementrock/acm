#include<stdio.h>
#include<string.h>
int f[21][21][21]={};
void dp(int a, int b, int c)
{
	if(a<=0||b<=0||c<=0)
	{
		f[a][b][c]=1;
		return;
	}
	if(a<b&&b<c)
	{
		if(f[a][b][c-1]==-1) dp(a,b,c-1);
		if(f[a][b-1][c-1]==-1) dp(a,b-1,c-1);
		if(f[a][b-1][c]==-1) dp(a,b-1,c);
		f[a][b][c]=f[a][b][c-1]+f[a][b-1][c-1]-f[a][b-1][c];
		return; 
	}
	if(f[a-1][b][c]==-1) dp(a-1,b,c);
	if(f[a-1][b-1][c]==-1) dp(a-1,b-1,c);
	if(f[a-1][b][c-1]==-1) dp(a-1,b,c-1);
	if(f[a-1][b-1][c-1]==-1) dp(a-1,b-1,c-1);
	f[a][b][c]=f[a-1][b][c]+f[a-1][b-1][c]+f[a-1][b][c-1]-f[a-1][b-1][c-1];
}
int main()
{
	memset(f,0xff,sizeof(f));
	int a,b,c;
	while(1)
	{
		scanf("%d%d%d",&a,&b,&c);
		if(a==-1&&b==-1&&c==-1) break;
		if(a<=0||b<=0||c<=0)
		{
			printf("w(%d, %d, %d) = %d\n",a,b,c,1);
		}
		else if(a>20||b>20||c>20)
		{
			if(f[20][20][20]==-1) dp(20,20,20);
			printf("w(%d, %d, %d) = %d\n",a,b,c,f[20][20][20]);
		}
		else
		{
			if(f[a][b][c]==-1) dp(a,b,c);
			printf("w(%d, %d, %d) = %d\n",a,b,c,f[a][b][c]);
		}
	}
}
