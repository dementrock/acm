#include<stdio.h>
#include<string.h>
int father[30001],n,m,ans;
int getfather(int x)
{
	return father[x]==x?x:father[x]=getfather(father[x]);
}
void together(int a, int b)
{
	father[getfather(a)]=getfather(b);
}
int main()
{
	while(scanf("%d%d",&n,&m))
	{
		int k,x,y;
		if(!n&&!m) break;
		for(int i=0;i<n;++i)
			father[i]=i;
		for(int i=1;i<=m;++i){
			scanf("%d",&k);
			scanf("%d",&x);
			for(int j=2;j<=k;++j){
				scanf("%d",&y);
				together(x,y);
			}
		}
		ans=1;
		int f=getfather(0);
		for(int i=1;i<n;++i)
			if(getfather(i)==f)
				++ans;
		printf("%d\n",ans);
	}
}
