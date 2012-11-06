#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int n,w,h,s,t,x,y,c[101][101],ans;
inline int max(int a, int b){
	return a>b?a:b;
}
void add(int a, int b, int d){
	for(int x=a;x<=w;x+=x&-x)
		for(int y=b;y<=h;y+=y&-y)
			c[x][y]+=d;
}
int getsum(int a, int b){
	int res=0;
	for(int x=a;x>0;x-=x&-x)
		for(int y=b;y>0;y-=y&-y){
			res+=c[x][y];
		}
	return res;
}
int main()
{
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		memset(c,0,sizeof(c));
		ans=0;
		scanf("%d%d",&w,&h);
		for(int i=1;i<=n;++i){
			scanf("%d%d",&x,&y);
			y=h+1-y;
			add(x,y,1);
		}
		scanf("%d%d",&s,&t);
		for(int i=s;i<=w;++i)
			for(int j=t;j<=h;++j)
				ans=max(ans,getsum(i,j)-getsum(i-s,j)-getsum(i,j-t)+getsum(i-s,j-t));
		printf("%d\n",ans);
	}
	return 0;
}
