#include<stdio.h>
#include<string.h>
#include<stdlib.h>
double comb(double x, double y)
{
	double result=1;
	double n=x>y?x:y;
	double m=x<y?x:y;
	for(double i=n+m;i>=n+1;--i)
		result*=i/(i-n);
	return result;
}
int main()
{
	while(1)
	{
		double n,m;
		scanf("%lf%lf",&n,&m);
		if(!n&&!m) break;
		printf("%.0lf\n",comb(n,m));
	}
	return 0;
}
