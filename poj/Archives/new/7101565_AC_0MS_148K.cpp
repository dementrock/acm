#include<stdio.h>
#include<stdlib.h>
int r,g,b,R[100],G[100],B[100];
int calc(int x1, int y1, int z1, int x2, int y2, int z2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2);
}
int main()
{
	for(int i=1;i<=16;++i)
		scanf("%d%d%d",&R[i],&G[i],&B[i]);
	while(1)
	{
		scanf("%d%d%d",&r,&g,&b);
		if(r==-1&&g==-1&&b==-1) break;
		int mint=99999999,mini;
		for(int i=1;i<=16;++i)
		{
			int t=calc(r,g,b,R[i],G[i],B[i]);
			if(t<mint)
			{
				mint=t;
				mini=i;
			}
		}
		printf("(%d,%d,%d) maps to (%d,%d,%d)\n",r,g,b,R[mini],G[mini],B[mini]);
	}
	return 0;
}
