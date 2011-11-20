#include<stdio.h>
int main()
{
	int n,m,f,g;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		int f,t=0;
		scanf("%d",&g);
		f=2*g-1;
		for(int i=2;i<=n;++i)
		{
			scanf("%d",&t);
			if(t==1)
				f=(2*g+t)%m;
			else f=(2*g+2*t+f)%m;
			g=(2*g+t)%m;
		}
		printf("%d\n",f);
	}
}
