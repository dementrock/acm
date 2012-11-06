#include<stdio.h>
int f[101],c[101];
int main()
{
	f[1]=1;
	c[1]=1;
	for(int i=2;i<=100;++i)
	{
		for(int j=1;j<=i/2;++j)
			if(!(i%j)) ++f[i];
		++f[i];
		//cout<<i<<" "<<f[i]<<endl;
		f[i]&=1;
		c[i]=c[i-1]+f[i];
	}
	int n,k;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&k);
		printf("%d\n",c[k]);
	}
	return 0;
}
