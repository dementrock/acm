#include<stdio.h>
int n,m,d,x[1001],y[1001],father[1001],avail[1001];
int getfather(int x)
{
	if(father[x]==x) return x;
	return father[x]=getfather(father[x]);
}
void together(int a, int b)
{
	int x=getfather(a),y=getfather(b);
	father[x]=y;
}
int main()
{
	char c;
	int p,q;
	scanf("%d %d\n",&n,&d);
	d*=d;
	for(int i=1;i<=n;++i)
	{
		scanf("%d %d\n",&x[i],&y[i]);
		father[i]=i;
	}
	while(1)
	{
		if(scanf("%c",&c)==EOF) break;
		if(c=='O')
		{
			scanf(" %d\n",&p);
			avail[p]=1;
			for(int j=1;j<=n;++j)
				if(avail[j]&&(x[j]-x[p])*(x[j]-x[p])+(y[j]-y[p])*(y[j]-y[p])<=d)
					together(j,p);
		}
		else
		{
			scanf(" %d %d\n",&p,&q);
			if(!avail[p]||!avail[q]||getfather(p)!=getfather(q))
				printf("FAIL\n");
			else
				printf("SUCCESS\n");
		}
	}
	return 0;
}
