#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	long long a,b;
	scanf("%I64d",&a);
	for(b=2*a+1;b>a;--b) 
		if((a*b+1)%(b-a)==0)
		{
			printf("%I64d\n",b+(a*b+1)/(b-a));
			break;
		}
	return 0;
}
