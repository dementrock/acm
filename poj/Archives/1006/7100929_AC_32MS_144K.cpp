#include<stdio.h>
int main()
{
	int r1=5544,r2=14421,r3=1288;
	int p,e,i,d,c=0;
	while(scanf("%d%d%d%d",&p,&e,&i,&d)!=EOF)
	{
		if(p<0) break;
		printf("Case %d: the next triple peak occurs in %d days.\n",++c,((r1*p+r2*e+r3*i-d+21252)%21252)?((r1*p+r2*e+r3*i-d+21252)%21252):21252);
	}
	return 0;
}
