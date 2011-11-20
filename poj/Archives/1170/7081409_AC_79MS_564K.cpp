#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int f[6][6][6][6][6]={},cgood[10],kgood[10],sprice[10],price[101],code[2000],num[101][2000],b,s,x,y,z;
inline int min(int a, int b){return a>b?b:a;}
void dp(int x1, int x2, int x3, int x4, int x5)
{
	f[x1][x2][x3][x4][x5]=x1*sprice[1]+x2*sprice[2]+x3*sprice[3]+x4*sprice[4]+x5*sprice[5];
	for(int i=1;i<=s;++i)
	{
		int t1=x1-num[i][1],t2=x2-num[i][2],t3=x3-num[i][3],t4=x4-num[i][4],t5=x5-num[i][5];
		if(t1>=0&&t2>=0&&t3>=0&&t4>=0&&t5>=0)
		{
			if(f[t1][t2][t3][t4][t5]==-1) dp(t1,t2,t3,t4,t5);
			f[x1][x2][x3][x4][x5]=min(f[x1][x2][x3][x4][x5],f[t1][t2][t3][t4][t5]+price[i]);
		}
	}
}
int main()
{
	memset(f,0xff,sizeof(f));
	scanf("%d",&b);
	for(int i=1;i<=b;++i)
	{
		scanf("%d%d%d",&cgood[i],&kgood[i],&sprice[i]);
		code[cgood[i]]=i;
	}
	scanf("%d",&s);
	for(int i=1;i<=s;++i)
	{
		scanf("%d",&x);
		for(int j=1;j<=x;++j)
		{
			scanf("%d%d",&y,&z);
			num[i][code[y]]=z;
		}
		scanf("%d",&price[i]);
	}
	if(f[kgood[1]][kgood[2]][kgood[3]][kgood[4]][kgood[5]]==-1)
		dp(kgood[1],kgood[2],kgood[3],kgood[4],kgood[5]);
	printf("%d\n",f[kgood[1]][kgood[2]][kgood[3]][kgood[4]][kgood[5]]);
	return 0;
}
