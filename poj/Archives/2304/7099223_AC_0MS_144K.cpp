#include<stdio.h>
#include<stdlib.h>
#include<string.h>
inline int min(int a, int b){return a>b?b:a;}
int main()
{
	int k,x,y,z;
	while(scanf("%d%d%d%d",&k,&x,&y,&z))
	{
		if(!x&&!y&&!z&&!k) break;
		printf("%d\n",9*(120+(k-x+40)%40+(y-x+40)%40+(y+40-z)%40));
	}
	return 0;
}
